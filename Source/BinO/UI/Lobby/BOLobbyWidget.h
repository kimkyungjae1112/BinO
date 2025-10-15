// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BOLobbyWidget.generated.h"

class UButton;
class UScrollBox;
class UBOServerRowWidget;
struct FBlueprintSessionResult;

UCLASS()
class BINO_API UBOLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreateGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FindGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ServerListContainer;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBOServerRowWidget> ServerRowWidgetClass;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void CreateGame();

	UFUNCTION()
	void FindGame();

	void OnServerListUpdated(const TArray<FBlueprintSessionResult>& ServerList);

};

