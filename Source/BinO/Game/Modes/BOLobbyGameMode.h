// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BOLobbyGameMode.generated.h"

class UBOLobbyWidget;

UCLASS()
class BINO_API ABOLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBOLobbyWidget> LobbyWidgetClass;

protected:
	virtual void BeginPlay() override;
};
