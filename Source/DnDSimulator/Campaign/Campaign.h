// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "../AllLevels/Hero.h"
#include "Campaign.generated.h"

const FString CAMPAIGN_DIRECTORY = "/Campaigns/";

UCLASS()
class DNDSIMULATOR_API ACampaign : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACampaign();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void LoadFromFile(FString campaignFile);

	UFUNCTION(BluePrintImplementableEvent, Category = "Initialization")
		void LoadCharacterListEvent();

	UPROPERTY(EditDefaultsOnly, Category = "Hero")
		TSubclassOf<AHero> AHeroBP;

	UPROPERTY(BlueprintReadWrite, Category = "Player Characters")
		TArray<AHero*> availableCharacters;
	
};
