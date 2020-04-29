// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBuilderController.h"

#include "Divider.h"

#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/BrushComponent.h"

constexpr float SQUARE_DISTANCE = 100.0f;
constexpr float HEX_DISTANCE_X = 100.0f;
constexpr float HEX_DISTANCE_Y = 86.6f; 
constexpr float ZLOC = 20.0f;

enum SpaceType
{
	HEX,
	SQUARE
};

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

void AMapBuilderController::SelectSpaceType(FString inputSpaceTypeStr)
{
	SpaceType inputSpaceType = HEX;

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
}

void AMapBuilderController::ClearSpaces()
{
	for (int i = 0; i < gridSpaces.Num(); i++)
	{
		//FString outStr = FString::Printf(TEXT("%i: "), i) + gridSpaces[i]->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, outStr);
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
			AGridSpace* hexRef = GetWorld()->SpawnActor<AGridSpace>(GridHex, FVector(xLoc, yLoc, ZLOC), FRotator(), spawnParams);
			int index = gridSpaces.Num();
			hexRef->SetIndex(index);
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
			hexRef->SetIndex(gridSpaces.Num());
			gridSpaces.Add(hexRef);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f, %f"), xLoc, yLoc));
		}
	}

	int midSpaceIndex = numSpaces / 2;
	gridSpaces[midSpaceIndex]->MoveCameraToSpace();
}

void AMapBuilderController::CalculateNeighborsHex(int index)
{
	AGridSpace* newNeighbor;
	if (index % dimension != 0)
	{
		newNeighbor = gridSpaces[index - 1];

		gridSpaces[index]->AddNeighbor(newNeighbor);
		newNeighbor->AddNeighbor(gridSpaces[index]);
	}

	if (index > dimension)
	{
		newNeighbor = gridSpaces[index - dimension];

		gridSpaces[index]->AddNeighbor(newNeighbor);
		newNeighbor->AddNeighbor(gridSpaces[index]);

		if ((index / dimension) % 2 == 1)
		{
			if (index % dimension != dimension - 1)
			{
				newNeighbor = gridSpaces[index - dimension + 1];

				gridSpaces[index]->AddNeighbor(newNeighbor);
				newNeighbor->AddNeighbor(gridSpaces[index]);
			}
		}
		else
		{
			if (index % dimension != 0)
			{
				newNeighbor = gridSpaces[index - dimension - 1];

				gridSpaces[index]->AddNeighbor(newNeighbor);
				newNeighbor->AddNeighbor(gridSpaces[index]);
			}
		}
	}
}

void AMapBuilderController::GridClick(AGridSpace* hitSpace)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Click"));
	for (int i = 0; i < gridSpaces.Num(); i++)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Click: %d"), i));
		gridSpaces[i]->SetHighlight(HL_NONE);
	}

	hitSpace->SetHighlight(HL_SELECTED);

	TArray<ADivider*> neighbors = hitSpace->GetNeighbors();

	for (int i = 0; i < neighbors.Num(); i++)
	{
		neighbors[i]->destination->SetHighlight(HL_ADJACENT);
	}
}

