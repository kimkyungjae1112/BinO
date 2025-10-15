// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Modes/BOLobbyGameMode.h"
#include "UI/Lobby/BOLobbyWidget.h"

void ABOLobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UBOLobbyWidget* LobbyWidget = CreateWidget<UBOLobbyWidget>(GetWorld(), LobbyWidgetClass))
	{
		LobbyWidget->AddToViewport();
	}
}
