// Used for general function calls. In particular, this allows blueprints to make quick calls to code that can only
//	be run in C++


#include "MyUtilities.h"
#include "HAL/FileManagerGeneric.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

// Sets default values
AMyUtilities::AMyUtilities()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Returns an array of FStrings listing every file in a directory with the provided extension
TArray<FString> AMyUtilities::GetFileNamesByDirectory(FString directory, FString extension)
{
	TArray<FString> retList;

	FFileManagerGeneric fileManager = FFileManagerGeneric();
	FString fullPath = FPaths::Combine(FPaths::ProjectDir(), directory);
	fileManager.FindFiles(retList, *fullPath, *extension);

	return retList;
}

FString AMyUtilities::GetTextFromFile(FString directory, FString filename)
{
	FString fullText;

	FFileManagerGeneric fileManager = FFileManagerGeneric();
	FString fullPath = FPaths::Combine(FPaths::ProjectDir(), directory + filename);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, fullPath);
	if (fileManager.FileExists(*fullPath))
	{
		//FArchive* fArchive = fileManager.CreateFileReader(*fullPath);
		FFileHelper::LoadFileToString(fullText, *fullPath);
	}

	return fullText;

}

UTexture2D* AMyUtilities::LoadTextureFromPath(FString directory, FString filename)
{
	FFileManagerGeneric fileManager = FFileManagerGeneric();
	FString fullPath = FPaths::Combine(FPaths::ProjectDir(), directory + filename);
	if (fileManager.FileExists(*fullPath))
	{
		return NULL;
	}

	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *fullPath));
}