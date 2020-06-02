// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyUtilities.generated.h"

UCLASS()
class DNDSIMULATOR_API AMyUtilities : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyUtilities();

	UFUNCTION(BlueprintCallable, Category = "FileManager")
		static TArray<FString> GetFileNamesByDirectory(FString directory, FString extension);

	UFUNCTION(BlueprintCallable, Category = "FileManager")
		static FString GetTextFromFile(FString directory, FString filename);

	static UTexture2D* LoadTextureFromPath(FString directory, FString filename);
};
