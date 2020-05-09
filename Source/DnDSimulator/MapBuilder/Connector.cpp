// Fill out your copyright notice in the Description page of Project Settings.

#include "Connector.h"
#include "GridSpace.h"

// Sets default values
AConnector::AConnector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isCorner = false;
}

// Called when the game starts or when spawned
void AConnector::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConnector::setCounterpart(AConnector* newCounterpart)
{
	counterpart = newCounterpart;
}


FString AConnector::ToOutputStr()
{
	FString outputStr = "" + this->conName;
	outputStr += "~";
	outputStr += this->GetActorLocation().ToCompactString();
	outputStr += "~";
	outputStr += FString::Printf(TEXT("%i%i"), allowMove, allowLOS);
	outputStr += "~";
	outputStr += FString::Printf(TEXT("%i"), destination->GetIndex());


	return outputStr;
}