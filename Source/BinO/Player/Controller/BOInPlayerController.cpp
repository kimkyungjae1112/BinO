// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Controller/BOInPlayerController.h"

void ABOInPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = false;
	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);
}
