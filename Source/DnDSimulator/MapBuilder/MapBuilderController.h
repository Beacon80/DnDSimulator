// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSpace.h"
#include "MapBuilderController.generated.h"



UCLASS()
class DNDSIMULATOR_API AMapBuilderController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapBuilderController();

	int dimension = 5;

	UFUNCTION(BlueprintCallable)
		void SelectSpaceType(FString inputSpaceTypeStr);

	UFUNCTION(BlueprintCallable, Category = "Click")
		void GridClick(AGridSpace* hitSpace);

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AGridSpace> GridHex;
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AGridSpace> GridSquare;

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

	TArray<AGridSpace*> gridSpaces;

	int numSpaces;
};
