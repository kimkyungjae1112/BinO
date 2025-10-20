// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BOSelectionClassWidget.generated.h"

class UButton;

UCLASS()
class BINO_API UBOSelectionClassWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonWraith;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonAurora;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonKallari;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonGideon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonTerra;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ChangeWraith();

	UFUNCTION()
	void ChangeAurora();

	UFUNCTION()
	void ChangeKallari();

	UFUNCTION()
	void ChangeGideon();

	UFUNCTION()
	void ChangeTerra();
};
