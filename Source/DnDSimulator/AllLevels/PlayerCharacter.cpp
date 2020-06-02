// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "MyUtilities.h"

const FString DIRECTORY = "/PlayerCharacters/";

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the attribute map if needed
	//if (attMap.Num() == 0) {
	//	attMap.Add("Name", ATT_NAME);
	//	attMap.Add("Model", ATT_MODEL);

	//	attMap.Add("Level", ATT_LEVEL);
	//	attMap.Add("L-HP", ATT_L_HP);

	//	attMap.Add("STR", ATT_STR);
	//	attMap.Add("DEX", ATT_DEX);
	//	attMap.Add("CON", ATT_CON);
	//	attMap.Add("INT", ATT_INT);
	//	attMap.Add("WIS", ATT_WIS);
	//	attMap.Add("CHA", ATT_CHA);
	//}
}

bool APlayerCharacter::LoadFromFile(FString characterFile)
{
	FString fullText = AMyUtilities::GetTextFromFile("/PlayerCharacters/", characterFile);

	TArray<FString> lines;
	fullText.ParseIntoArrayLines(lines, true);

	for (int i = 0; i < lines.Num(); i++)
	{
		TArray<FString> keyval;
		FString separator = ":";
		lines[i].ParseIntoArray(keyval, *separator, true);

		if (keyval.Num() != 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Could not read line: " + lines[i]);
			return false;
		}


		//if (!attMap.Contains(keyval[0]))
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Could not read attribute: " + keyval[0]);
		//	return false;
		//}
	//	Attribute attribute = attMap[keyval[0]];

	//	switch (attribute)
	//	{
	//	case ATT_NAME:
	//		pcName = keyval[0];
	//		break;

	//	case ATT_MODEL:
	//		// Temp
	//		model = keyval[0];
	//		break;

	//	case ATT_LEVEL:
	//		break;

	//	case ATT_L_HP:
	//		break;

	//	case ATT_STR:
	//		abilityScores.Add(AS_STR, FCString::Atoi(*keyval[0]));
	//		break;

	//	case ATT_DEX:
	//		abilityScores.Add(AS_DEX, FCString::Atoi(*keyval[0]));
	//		break;

	//	case ATT_CON:
	//		abilityScores.Add(AS_CON, FCString::Atoi(*keyval[0]));
	//		break;

	//	case ATT_INT:
	//		abilityScores.Add(AS_INT, FCString::Atoi(*keyval[0]));
	//		break;

	//	case ATT_WIS:
	//		abilityScores.Add(AS_WIS, FCString::Atoi(*keyval[0]));
	//		break;

	//	case ATT_CHA:
	//		abilityScores.Add(AS_CHA, FCString::Atoi(*keyval[0]));
	//		break;
	//	}
	}

	return true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString APlayerCharacter::ToString()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Name: " + pcName);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "\tSTR: " + abilityScores[AS_STR]);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "\tDEX: " + abilityScores[AS_DEX]);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "\tCON: " + abilityScores[AS_CON]);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "\tINT: " + abilityScores[AS_INT]);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "\tWIS: " + abilityScores[AS_WIS]);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "\tCHA: " + abilityScores[AS_CHA]);

	return pcName;
}
