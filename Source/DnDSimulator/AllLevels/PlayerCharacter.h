// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.generated.h"

//UENUM(BlueprintType)
//enum AbilityScores
//{
//	STRENGTH = 0,
//	DEXTERITY = 1,
//	CONSTITUTION = 2,
//	INTELLIGENCE = 3,
//	WISDOM = 4,
//	CHARISMA = 5
//};

//UENUM(BlueprintType)
//enum AbilityScore
//{
//	AS_STR,
//	AS_DEX,
//	AS_CON,
//	AS_INT,
//	AS_WIS,
//	AS_CHA
//};
//
//enum Attribute
//{
//	ATT_NAME,
//	ATT_MODEL,
//
//	ATT_LEVEL,
//	ATT_L_HP,
//	
//	ATT_STR,
//	ATT_DEX,
//	ATT_CON,
//	ATT_INT,
//	ATT_WIS,
//	ATT_CHA,
//
//	ATT_HP
//
//};

//static TMap<FString, Attribute> attMap = TMap<FString, Attribute>();

UCLASS()
class DNDSIMULATOR_API APlayerCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCharacter();

	bool LoadFromFile(FString characterFile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString ToString();

	int curHP, maxHP;

	FString pcName;

	// Temp way of handling model
	FString model;

	//TMap<AbilityScore, int> abilityScores = TMap<AbilityScore, int>();
};
