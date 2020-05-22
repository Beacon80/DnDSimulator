// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSpace.h"
#include "MapBuilderController.generated.h"

UENUM(BlueprintType)
enum SpaceType
{
	NONE,
	HEX,
	SQUARE
};



UCLASS()
class DNDSIMULATOR_API AMapBuilderController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapBuilderController();

	UFUNCTION(BlueprintCallable, Category = "Map")
		void CreateMap(FString inputSpaceTypeStr, int newDimension);

	UFUNCTION(BlueprintCallable, Category = "Click")
		void GridClick(AGridSpace* hitSpace);

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AGridSpace> GridHex;
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AGridSpace> GridSquare;

	UFUNCTION(BlueprintCallable, Category = "GridSpace Properties")
		void SaveMap(FString mapName);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ClearSpaces();
	void BuildHexes();
	void BuildSquares();

	void CalculateNeighborsHex(int index);
	void CalculateNeighborsSquare(int index);
	void BuildConnectors(AGridSpace* space1, AGridSpace* space2, bool isCorner = false);

	FString ConvertIndexToCoords(int index);

	TArray<AGridSpace*> gridSpaces;

	SpaceType inputSpaceType;
	int numSpaces;

	int dimension = 5;
};
