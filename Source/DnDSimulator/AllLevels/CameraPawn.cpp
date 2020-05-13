// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Constructor")));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.0f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	// Take control of default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Tick")));

	// Zoom in if button is down
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / ZoomInSpeed;
	}
	else
	{
		ZoomFactor -= DeltaTime / ZoomOutSpeed;
	}

	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	
	// Blend our camera's FOV and our SpringArm's length baed on ZoomFactor
	OurCamera->FieldOfView = FMath::Lerp<float>(ZoomFOVMax, ZoomFOVMin, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(ZoomBaseDist, ZoomBaseDist * ZoomInBound, ZoomFactor);

	// Rotate actor's yaw, turning camera
	FRotator NewYaw = GetActorRotation();
	NewYaw.Yaw += CameraInput.X;
	SetActorRotation(NewYaw);

	// Rotate pitch, but limit it to downward directions
	FRotator NewPitch = OurCameraSpringArm->GetComponentRotation();
	NewPitch.Pitch = FMath::Clamp(NewPitch.Pitch + CameraInput.Y, PitchMin, PitchMax);

	// Lateral movement
	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * MoveRate;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Setup")));

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACameraPawn::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Released, this, &ACameraPawn::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &ACameraPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACameraPawn::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ACameraPawn::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &ACameraPawn::YawCamera);
}

// Input functions
void ACameraPawn::MoveForward(float AxisValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MoveForward")));
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}
void ACameraPawn::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}
void ACameraPawn::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}
void ACameraPawn::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}
void ACameraPawn::ZoomIn()
{
	bZoomingIn = true;
}
void ACameraPawn::ZoomOut()
{
	bZoomingIn = false;
}