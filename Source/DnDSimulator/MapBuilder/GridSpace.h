// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Divider.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSpace.generated.h"

enum GridHighlight {
	HL_NONE,
	HL_SELECTED,
	HL_ADJACENT
};

UCLASS()
class DNDSIMULATOR_API AGridSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSpace();
	//~AGridSpace();

	UFUNCTION(BluePrintImplementableEvent, Category = "Camera")
		void MoveCameraToSpace();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		int GetIndex();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void AddDivider(ADivider* neighbor);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void AddNeighbor(AGridSpace* neighbor);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		ADivider* GetNeighbor(int index);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		TArray<ADivider*> GetNeighbors();


	void SetIndex(int newIndex);

	void SetHighlight(GridHighlight gh);
	UFUNCTION(BluePrintImplementableEvent, Category = "Camera")
		void SetHighlightBP(int gh);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	uint64 index;

	TArray<ADivider*> dividers;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
