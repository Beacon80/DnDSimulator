// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBuilderController.h"

#include "Connector.h"

#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/BrushComponent.h"

#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"

constexpr float SQUARE_DISTANCE = 100.0f;
constexpr float HEX_DISTANCE_X = 100.0f;
constexpr float HEX_DISTANCE_Y = 86.6f; 
constexpr float ZLOC = 20.0f;

// Sets default values
AMapBuilderController::AMapBuilderController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	dimension = 5;

}

// Called when the game starts or when spawned
void AMapBuilderController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMapBuilderController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapBuilderController::CreateMap(FString inputSpaceTypeStr, int newDimension)
{
	dimension = newDimension;
	inputSpaceType = NONE;

	if (inputSpaceTypeStr == "Hex")
	{
		inputSpaceType = HEX;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hex"));

		if (GridHex)
		{
			BuildHexes();
		}
	}

	else if (inputSpaceTypeStr == "Square")
	{
		inputSpaceType = SQUARE;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Square"));
		BuildSquares();
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error! Could not read type:"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, inputSpaceTypeStr);
	}
}

void AMapBuilderController::ClearSpaces()
{
	for (int i = 0; i < gridSpaces.Num(); i++)
	{
		gridSpaces[i]->ClearConnectors();
		gridSpaces[i]->Destroy();
	}

	gridSpaces.Empty();
}

void AMapBuilderController::BuildHexes()
{
	ClearSpaces();

	FActorSpawnParameters spawnParams;
	numSpaces = dimension * dimension;

	bool yOffset = 0;

	for (int j = 0; j < dimension; j++)
	{
		float yLoc = (float) j * HEX_DISTANCE_Y;
		for (int i = 0; i < dimension; i++)
		{
			float xLoc = (float) i * HEX_DISTANCE_X;
			if (yOffset)
			{
				xLoc += 0.5 * HEX_DISTANCE_Y;
			}
			AGridSpace* hexRef = GetWorld()->SpawnActor<AGridSpace>(GridHex, FVector(xLoc, yLoc, ZLOC), FRotator(0.f, 0.f, 0.f), spawnParams);
			int index = gridSpaces.Num();
			hexRef->SetIndex(index);
			FString newName = ConvertIndexToCoords(index);
			hexRef->gsName = newName;
			gridSpaces.Add(hexRef);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f, %f"), xLoc, yLoc));

			CalculateNeighborsHex(index);
		}
		yOffset = !yOffset;
	}

	int midSpaceIndex = numSpaces / 2;
	gridSpaces[midSpaceIndex]->MoveCameraToSpace();
}

void AMapBuilderController::BuildSquares()
{
	ClearSpaces();

	FActorSpawnParameters spawnParams;
	numSpaces = dimension * dimension;

	for (int j = 0; j < dimension; j++)
	{
		float yLoc = (float)j * SQUARE_DISTANCE;
		for (int i = 0; i < dimension; i++)
		{
			float xLoc = (float)i * SQUARE_DISTANCE;
			AGridSpace* hexRef = GetWorld()->SpawnActor<AGridSpace>(GridSquare, FVector(xLoc, yLoc, ZLOC), FRotator(), spawnParams);
			int index = gridSpaces.Num();
			hexRef->SetIndex(index);
			FString newName = ConvertIndexToCoords(index);
			hexRef->gsName = newName;
			gridSpaces.Add(hexRef);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f, %f"), xLoc, yLoc));

			CalculateNeighborsSquare(index);
		}
	}

	int midSpaceIndex = numSpaces / 2;
	gridSpaces[midSpaceIndex]->MoveCameraToSpace();
}

FString AMapBuilderController::ConvertIndexToCoords(int index)
{
	char xCoord;
	char yCoord;

	xCoord = 'A' + (index % dimension);
	yCoord = '1' + (index / dimension);

	return FString::Printf(TEXT("%c%c"), xCoord, yCoord);
}

void AMapBuilderController::CalculateNeighborsHex(int index)
{
	AGridSpace* newNeighbor;
	if (index % dimension != 0)
	{
		newNeighbor = gridSpaces[index - 1];

		BuildConnectors(gridSpaces[index], newNeighbor);
	}

	if (index >= dimension)
	{
		newNeighbor = gridSpaces[index - dimension];

		BuildConnectors(gridSpaces[index], newNeighbor);

		if ((index / dimension) % 2 == 1)
		{
			if (index % dimension != dimension - 1)
			{
				newNeighbor = gridSpaces[index - dimension + 1];

				BuildConnectors(gridSpaces[index], newNeighbor);
			}
		}
		else
		{
			if (index % dimension != 0)
			{
				newNeighbor = gridSpaces[index - dimension - 1];

				BuildConnectors(gridSpaces[index], newNeighbor);
			}
		}
	}
}

void AMapBuilderController::CalculateNeighborsSquare(int index)
{
	AGridSpace* newNeighbor;
	if (index % dimension != 0)
	{
		newNeighbor = gridSpaces[index - 1];

		BuildConnectors(gridSpaces[index], newNeighbor);
	}

	if (index >= dimension)
	{
		newNeighbor = gridSpaces[index - dimension];

		BuildConnectors(gridSpaces[index], newNeighbor);

		if (index % dimension != 0)
		{
			newNeighbor = gridSpaces[index - dimension - 1];

			BuildConnectors(gridSpaces[index], newNeighbor, true);
		}

		if (index % dimension != dimension - 1)
		{
			newNeighbor = gridSpaces[index - dimension + 1];

			BuildConnectors(gridSpaces[index], newNeighbor, true);
		}
	}
}

void AMapBuilderController::BuildConnectors(AGridSpace* space1, AGridSpace* space2, bool isCorner)
{
	AConnector* div1 = space1->AddNeighbor(space2, isCorner);
	AConnector* div2 = space2->AddNeighbor(space1, isCorner);

	div1->setCounterpart(div2);
	div2->setCounterpart(div1);
}

void AMapBuilderController::GridClick(AGridSpace* hitSpace)
{
	for (int i = 0; i < gridSpaces.Num(); i++)
	{
		gridSpaces[i]->SetHighlight(HL_NONE);
	}

	hitSpace->SetHighlight(HL_SELECTED);

	TArray<AConnector*> neighbors = hitSpace->GetNeighbors();

	for (int i = 0; i < neighbors.Num(); i++)
	{
		if (neighbors[i]->isCorner)
		{
			neighbors[i]->destination->SetHighlight(HL_CORNER);
		}
		else
		{
			neighbors[i]->destination->SetHighlight(HL_ADJACENT);
		}
	}
}

void AMapBuilderController::SaveMap(FString mapName)
{
	if (inputSpaceType == NONE || gridSpaces.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Map has not been initialized.")));
		return;
	}
	FString output = FString::Printf(TEXT("%i"), inputSpaceType);;
	for (int i = 0; i < gridSpaces.Num(); i++)
	{
		output += '\n';
		output += gridSpaces[i]->ToOutputStr();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, output);

	FString path = FPaths::ProjectDir();
	path += "/Maps";

	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*path))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*path);
	}
	
	path += "/" + mapName + ".dndm";

	FFileHelper::SaveStringToFile(output, *path);
}