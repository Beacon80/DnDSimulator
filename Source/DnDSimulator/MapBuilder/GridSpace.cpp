// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSpace.h"

#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/BrushComponent.h"


// Sets default values
AGridSpace::AGridSpace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Deconstructor
void AGridSpace::ClearConnectors()
{
	for (int i = 0; i < connectors.Num(); i++)
	{
		connectors[i]->Destroy();
	}

}

// Called when the game starts or when spawned
void AGridSpace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGridSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridSpace::SetIndex(int newIndex)
{
	index = newIndex;
}

int AGridSpace::GetIndex()
{
	return index;
}

void AGridSpace::AddConnector(AConnector* neighbor)
{
	connectors.Add(neighbor);
}

AConnector* AGridSpace::AddNeighbor(AGridSpace* neighbor, bool isCorner)
{
	FActorSpawnParameters spawnParams;

	FVector divLoc = (neighbor->GetActorLocation() + this->GetActorLocation()) / 2;
	divLoc.Z = 15.0f;
	AConnector* newConnector = GetWorld()->SpawnActor<AConnector>(ConnectorBP, divLoc, FRotator(0.f, 0.f, 0.f), spawnParams);

	newConnector->destination = neighbor;
	newConnector->isCorner = isCorner;
	newConnector->SetActorHiddenInGame(true);
	FString label = this->GetActorLabel();
	label.Append("-");
	label.Append(neighbor->GetActorLabel());
	newConnector->SetActorLabel(label);

	connectors.Add(newConnector);

	return newConnector;
}

AConnector* AGridSpace::GetNeighbor(int neighborIndex)
{
	if (neighborIndex < 0 || neighborIndex >= connectors.Num())
	{
		return NULL;
	}

	return connectors[neighborIndex];
}

TArray<AConnector*> AGridSpace::GetNeighbors()
{
	return connectors;
}

void AGridSpace::setConnectorVisibility(bool vis)
{
	for (int i = 0; i < connectors.Num(); i++)
	{
		connectors[i]->SetActorHiddenInGame(!vis);
	}
}


void AGridSpace::SetHighlight(GridHighlight gh)
{
	switch (gh)
	{
	case HL_NONE:
		setConnectorVisibility(false);
		SetHighlightBP(0);
		break;

	case HL_SELECTED:
		setConnectorVisibility(true);
		SetHighlightBP(1);
		break;

	case HL_ADJACENT:
		setConnectorVisibility(false);
		SetHighlightBP(2);
		break;

	case HL_CORNER:
		setConnectorVisibility(false);
		SetHighlightBP(3);
		break;
	}
}

FString AGridSpace::ToOutputStr()
{
	FString outputStr = this->GetActorLabel();
	outputStr += ",";
	outputStr += this->GetActorLocation().ToCompactString();
	outputStr += ",";
	outputStr += FString::Printf(TEXT("%i%i%i"), roughSpace, allowMove, allowLOS);


	return outputStr;
}