// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BOCharacterBase.h"
#include "BOCharacterPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBOClassData;
class UBOInputData;
struct FInputActionValue;

UCLASS()
class BINO_API ABOCharacterPlayer : public ABOCharacterBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Player | Camera")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Player | Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

// Data
protected:
	UPROPERTY(EditAnywhere, Category = "Player | Data")
	TObjectPtr<UBOClassData> ClassData;

	UPROPERTY(EditAnywhere, Category = "Player | Input")
	TObjectPtr<UBOInputData> InputData;

public:
	ABOCharacterPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
