// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "MyUtilities.h"

const FString DIRECTORY = "/PlayerCharacters/";

// Sets default values
AHero::AHero()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the attribute map if needed
	if (attMap.Num() == 0) {
		attMap.Add("Name", ATT_NAME);
		attMap.Add("Portrait", ATT_PORTRAIT);
		attMap.Add("Model", ATT_MODEL);

		attMap.Add("Level", ATT_LEVEL);
		attMap.Add("L-HP", ATT_L_HP);

		attMap.Add("STR", ATT_STR);
		attMap.Add("DEX", ATT_DEX);
		attMap.Add("CON", ATT_CON);
		attMap.Add("INT", ATT_INT);
		attMap.Add("WIS", ATT_WIS);
		attMap.Add("CHA", ATT_CHA);
	}
}

bool AHero::LoadFromFile(FString characterFile)
{
	FString fullText = AMyUtilities::GetTextFromFile("/PlayerCharacters/", characterFile);

	TArray<FString> lines;
	fullText.ParseIntoArrayLines(lines, true);

	for (int i = 0; i < lines.Num(); i++)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Line: " + lines[i]);
		TArray<FString> keyval;
		FString separator = ":";
		lines[i].ParseIntoArray(keyval, *separator, true);

		if (keyval.Num() != 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Could not read line: " + lines[i]);
			return false;
		}


		if (!attMap.Contains(keyval[0]))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Could not read attribute: " + keyval[0]);
			return false;
		}
		Attribute attribute = attMap[keyval[0]];
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, keyval[0]);

		switch (attribute)
		{
		case ATT_NAME:
			pcName = keyval[1].Trim();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Name: " + pcName);
			break;

		case ATT_PORTRAIT:
			portrait = AMyUtilities::LoadTextureFromPath("/PlayerCharacters/Portraits", keyval[1]);
			if (portrait == NULL)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Could not load portrait: " + keyval[1]);
				//return false;
			}
			break;

		case ATT_MODEL:
			// Temp
			model = keyval[1];
			break;

		case ATT_LEVEL:
			break;

		case ATT_L_HP:
			break;

		case ATT_STR:
			abilityScores.Add(AS_STR, FCString::Atoi(*keyval[1]));
			break;

		case ATT_DEX:
			abilityScores.Add(AS_DEX, FCString::Atoi(*keyval[1]));
			break;

		case ATT_CON:
			abilityScores.Add(AS_CON, FCString::Atoi(*keyval[1]));
			break;

		case ATT_INT:
			abilityScores.Add(AS_INT, FCString::Atoi(*keyval[1]));
			break;

		case ATT_WIS:
			abilityScores.Add(AS_WIS, FCString::Atoi(*keyval[1]));
			break;

		case ATT_CHA:
			abilityScores.Add(AS_CHA, FCString::Atoi(*keyval[1]));
			break;
		}
	}

	if (!abilityScores.Contains(AS_STR)
		|| !abilityScores.Contains(AS_DEX)
		|| !abilityScores.Contains(AS_CON)
		|| !abilityScores.Contains(AS_INT)
		|| !abilityScores.Contains(AS_WIS)
		|| !abilityScores.Contains(AS_CHA))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Missing Stat");
		if (!abilityScores.Contains(AS_STR))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "\tMissing STR");
		}
		if (!abilityScores.Contains(AS_DEX))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "\tMissing DEX");
		}
		if (!abilityScores.Contains(AS_CON))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "\tMissing CON");
		}
		if (!abilityScores.Contains(AS_INT))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "\tMissing INT");
		}
		if (!abilityScores.Contains(AS_WIS))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "\tMissing WIS");
		}
		if (!abilityScores.Contains(AS_CHA))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "\tMissing CHA");
		}

		return false;
	}

	updateModifiers();

	return true;
}

void AHero::updateModifiers()
{
	int mod;

	mod = floor(abilityScores[AS_STR] / 2.0 - 5.0);
	abilityModifiers.Add(AS_STR, mod);
	mod = floor(abilityScores[AS_DEX] / 2.0 - 5.0);
	abilityModifiers.Add(AS_DEX, mod);
	mod = floor(abilityScores[AS_CON] / 2.0 - 5.0);
	abilityModifiers.Add(AS_CON, mod);
	mod = floor(abilityScores[AS_INT] / 2.0 - 5.0);
	abilityModifiers.Add(AS_INT, mod);
	mod = floor(abilityScores[AS_WIS] / 2.0 - 5.0);
	abilityModifiers.Add(AS_WIS, mod);
	mod = floor(abilityScores[AS_CHA] / 2.0 - 5.0);
	abilityModifiers.Add(AS_CHA, mod);
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AHero::StatToString(AbilityScore as)
{
	FString statString;
	statString += FString::FromInt(abilityScores[as]) + " (";

	if (abilityModifiers[as] > 0)
	{
		statString += "+";
	}

	statString += FString::FromInt(abilityModifiers[as]) + ")";

	return statString;
}

FString AHero::ToString()
{
	FString pcString = pcName + "\n";

	pcString += "STR> " + StatToString(AS_STR) + "\n";
	pcString += "DEX> " + StatToString(AS_DEX) + "\n";
	pcString += "CON> " + StatToString(AS_CON) + "\n";
	pcString += "INT> " + StatToString(AS_INT) + "\n";
	pcString += "WIX> " + StatToString(AS_WIS) + "\n";
	pcString += "CHA> " + StatToString(AS_CHA) + "\n";

	return pcString;
}

int AHero::GetAbilityScore(AbilityScore as)
{
	return abilityScores[as];
}

int AHero::GetAbilityModifier(AbilityScore as)
{
	return abilityModifiers[as];
}

UTexture2D* AHero::GetPortrait()
{
	return portrait;
}