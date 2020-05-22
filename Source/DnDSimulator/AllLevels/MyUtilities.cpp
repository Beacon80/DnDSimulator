// Used for general function calls. In particular, this allows blueprints to make quick calls to code that can only
//	be run in C++


#include "HAL/FileManagerGeneric.h"
#include "MyUtilities.h"

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
	fileManager.FindFiles(retList, *directory, *extension);

	return retList;
}