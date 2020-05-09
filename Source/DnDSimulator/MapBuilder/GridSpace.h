// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Connector.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSpace.generated.h"

UENUM(BlueprintType)
enum GridHighlight {
	HL_NONE,
	HL_SELECTED,
	HL_ADJACENT,
	HL_CORNER
};

UCLASS()
class DNDSIMULATOR_API AGridSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSpace();

	UFUNCTION(BluePrintImplementableEvent, Category = "Camera")
		void MoveCameraToSpace();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		int GetIndex();

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AConnector> ConnectorBP;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void AddConnector(AConnector* neighbor);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		AConnector* AddNeighbor(AGridSpace* neighbor, bool isCorner = false);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		AConnector* GetNeighbor(int index);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		TArray<AConnector*> GetNeighbors();


	void SetIndex(int newIndex);

	void SetHighlight(GridHighlight gh);
	UFUNCTION(BluePrintImplementableEvent, Category = "Camera")
		void SetHighlightBP(int gh);

	void ClearConnectors();

	UPROPERTY(BlueprintReadOnly, Category = "Grid Space")
		TArray<AConnector*> connectors;

	UPROPERTY(BlueprintReadWrite, Category = "Grid Space Attribute")
		FString gsName;
	UPROPERTY(BlueprintReadWrite, Category = "Grid Space Attribute")
		bool roughSpace = false;
	UPROPERTY(BlueprintReadWrite, Category = "Grid Space Attribute")
		bool allowMove = true;
	UPROPERTY(BlueprintReadWrite, Category = "Grid Space Attribute")
		bool allowLOS = true;

	FString ToOutputStr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int index;

	void setConnectorVisibility(bool vis);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
