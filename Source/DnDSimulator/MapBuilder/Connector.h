// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Connector.generated.h"

class AGridSpace;

UCLASS()
class DNDSIMULATOR_API AConnector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConnector();

	AGridSpace* destination;
	bool isCorner;

	void setCounterpart(AConnector* newCounterpart);

	UPROPERTY(BlueprintReadWrite, Category = "Connector Attribute")
		bool allowMove = true;
	UPROPERTY(BlueprintReadWrite, Category = "Connector Attribute")
		bool allowLOS = true;

	UPROPERTY(BlueprintReadOnly, Category = "Connector Attribute")
		AConnector* counterpart;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
