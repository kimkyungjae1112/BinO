// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"
#include "BOServerRowWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class BINO_API UBOServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ServerNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerCountText;

	FBlueprintSessionResult SessionResult;

public:
	void Setup(const FBlueprintSessionResult& InSessionResult);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnJoinButtonClicked();
};
