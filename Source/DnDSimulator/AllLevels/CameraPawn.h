// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class DNDSIMULATOR_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;

	// Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

	// Zoom variables
	UPROPERTY(EditAnywhere)
		float ZoomInSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
		float ZoomOutSpeed = 0.25f;
	UPROPERTY(EditAnywhere)
		float ZoomFOVMax = 90.0f;
	UPROPERTY(EditAnywhere)
		float ZoomFOVMin = 60.0f;
	UPROPERTY(EditAnywhere)
		float ZoomBaseDist = 400.0f;
	UPROPERTY(EditAnywhere)
		float ZoomInBound = 0.66f;

	UPROPERTY(EditAnywhere)
		float PitchMin = -80.0f;
	UPROPERTY(EditAnywhere)
		float PitchMax = -15.0f;
	UPROPERTY(EditAnywhere)
		float MoveRate = 100.0f;

	// Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();
};
