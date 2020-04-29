// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSpace.h"

// Sets default values
AGridSpace::AGridSpace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

void AGridSpace::AddDivider(ADivider* neighbor)
{
	dividers.Add(neighbor);
}

void AGridSpace::AddNeighbor(AGridSpace* neighbor)
{
	ADivider* newDivider = GetWorld()->SpawnActor<ADivider>();
	newDivider->destination = neighbor;

	dividers.Add(newDivider);
}

ADivider* AGridSpace::GetNeighbor(int neighborIndex)
{
	if (neighborIndex < 0 || neighborIndex >= dividers.Num())
	{
		return NULL;
	}

	return dividers[neighborIndex];
}

TArray<ADivider*> AGridSpace::GetNeighbors()
{
	return dividers;
}


void AGridSpace::SetHighlight(GridHighlight gh)
{
	switch (gh)
	{
	case HL_NONE:
		SetHighlightBP(0);
		break;

	case HL_SELECTED:
		SetHighlightBP(1);
		break;

	case HL_ADJACENT:
		SetHighlightBP(2);
		break;
	}
}