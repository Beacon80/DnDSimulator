// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Hero.generated.h"

UENUM(BlueprintType)
enum AbilityScore
{
	AS_STR,
	AS_DEX,
	AS_CON,
	AS_INT,
	AS_WIS,
	AS_CHA
};

enum Attribute
{
	ATT_NAME,
	ATT_PORTRAIT,
	ATT_MODEL,

	ATT_LEVEL,
	ATT_L_HP,

	ATT_STR,
	ATT_DEX,
	ATT_CON,
	ATT_INT,
	ATT_WIS,
	ATT_CHA,

	ATT_HP

};

static TMap<FString, Attribute> attMap = TMap<FString, Attribute>();

UCLASS()
class DNDSIMULATOR_API AHero : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHero();
	AActor *Owner;

	bool LoadFromFile(FString characterFile);
	void updateModifiers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Print")
		FString StatToString(AbilityScore as);
	UFUNCTION(BlueprintCallable, Category = "Print")
		FString ToString();

	int curHP, maxHP;

	UPROPERTY(BlueprintReadWrite, replicated, Category = "Display")
	//UPROPERTY(replicated, Category = "Display")
		FString pcName;
	UFUNCTION(BlueprintCallable, Category = "Display")
		FString GetPCName();
	UFUNCTION(BlueprintCallable, Category = "Display")
		void SetPCName(FString newName);
	UPROPERTY(BlueprintReadOnly, Category = "Display")
		UTexture2D* portrait;
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		UTexture2D* GetPortrait();
	// Temp way of handling model
	FString model;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		int GetAbilityScore(AbilityScore as);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		int GetAbilityModifier(AbilityScore as);

	TMap<AbilityScore, int> abilityScores = TMap<AbilityScore, int>();

	TMap<AbilityScore, int> abilityModifiers = TMap<AbilityScore, int>();
};
