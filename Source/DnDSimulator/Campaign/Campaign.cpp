// Fill out your copyright notice in the Description page of Project Settings.

#include "Campaign.h"
#include "../AllLevels/MyUtilities.h"

// Sets default values
ACampaign::ACampaign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACampaign::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACampaign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACampaign::LoadFromFile(FString campaignFile)
{
	FString fullText = AMyUtilities::GetTextFromFile(CAMPAIGN_DIRECTORY, campaignFile);
	FActorSpawnParameters spawnParams;
	availableCharacters.Empty();

	TArray<FString> lines;
	fullText.ParseIntoArrayLines(lines, true);

	for (int i = 0; i < lines.Num(); i++)
	{
		TArray<FString> keyval;
		FString separator = ":";
		lines[i].ParseIntoArray(keyval, *separator, true);
		if (keyval[0].Equals("PC"))
		{
			AHero* pcRef = GetWorld()->SpawnActor<AHero>(AHeroBP, FVector(0.0f, 0.0f, -200.0f), FRotator(0.f, 0.f, 0.f), spawnParams);
			bool success = false;
			success = pcRef->LoadFromFile(keyval[1]);
			if (success)
			{
				pcRef->SetReplicates(true);
				availableCharacters.Add(pcRef);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%i"), i));
			}
			else
			{
				GetWorld()->DestroyActor(pcRef);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Could not load character: " + keyval[1]);
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, availableCharacters[0]->ToString());
	LoadCharacterListEvent();
}
