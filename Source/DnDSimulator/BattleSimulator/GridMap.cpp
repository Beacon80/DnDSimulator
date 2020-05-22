// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMap.h"

// Sets default values
AGridMap::AGridMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Builds an empty map
  *
  * Input
  * inputSpaceTypeStr - Indicates hexes or squares. Not implemented yet. Convert to enum later
  * newDimention - int for the dimensions of the map
  */

void AGridMap::BuildEmptyMap(FString inputSpaceTypeStr, int newDimension)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Test1"));
	CreateMap(inputSpaceTypeStr, newDimension);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Test2"));
}
/*
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
}*/

