// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Divider.generated.h"

class AGridSpace;

UCLASS()
class DNDSIMULATOR_API ADivider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADivider();
	AGridSpace* destination;
	bool isCorner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
