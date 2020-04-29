// Fill out your copyright notice in the Description page of Project Settings.

#include "Divider.h"

// Sets default values
ADivider::ADivider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isCorner = false;
}

// Called when the game starts or when spawned
void ADivider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADivider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

