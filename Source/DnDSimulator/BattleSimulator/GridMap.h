// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../MapBuilder/MapBuilderController.h"

#include "GridMap.generated.h"

UCLASS()
class DNDSIMULATOR_API AGridMap : public AMapBuilderController
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void BuildEmptyMap(FString inputSpaceTypeStr, int newDimension);

};
