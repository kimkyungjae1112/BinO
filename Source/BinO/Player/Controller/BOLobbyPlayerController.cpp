// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Controller/BOLobbyPlayerController.h"

void ABOLobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	FInputModeUIOnly UIOnly;
	SetInputMode(UIOnly);
}
