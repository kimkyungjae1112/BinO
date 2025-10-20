// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BOCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Data/Class/BOClassData.h"
#include "Data/Input/BOInputData.h"
#include "Animation/AnimInstance.h"
#include "Player/Controller/BOLobbyPlayerController.h"

ABOCharacterPlayer::ABOCharacterPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 450.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
}

void ABOCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(InputData->IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInputComponent->BindAction(InputData->IA_SelectionClass, ETriggerEvent::Started, this, &ThisClass::DisplaySelectionClassWidget);
	}
}

void ABOCharacterPlayer::ChangeClass(UBOClassData* InClassData)
{
	if (InClassData)
	{
		GetMesh()->SetSkeletalMesh(InClassData->SkeletalMesh);
		GetMesh()->SetAnimInstanceClass(InClassData->AnimBP);
	}
}

void ABOCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->IMC_Default, 0);
		}
	}

	if (ClassData)
	{
		GetMesh()->SetSkeletalMesh(ClassData->SkeletalMesh);
		GetMesh()->SetAnimInstanceClass(ClassData->AnimBP);
	}
}

void ABOCharacterPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, InputValue.X);
	AddMovementInput(RightVector, InputValue.Y);
}

void ABOCharacterPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();
	
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(-InputValue.Y);
}

void ABOCharacterPlayer::DisplaySelectionClassWidget()
{
	if (ABOLobbyPlayerController* PC = Cast<ABOLobbyPlayerController>(GetController()))
	{
		PC->ToggleSelectionWidget();
	}
}
