// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Controller/BOLobbyPlayerController.h"
#include "Characters/BOCharacterPlayer.h"
#include "UI/Lobby/BOLobbyWidget.h"

void ABOLobbyPlayerController::ChangeClass(const EClassType& InClassType)
{
	if (GetPawn())
	{
		UWorld* World = GetWorld();
		FVector BOSpawnLocation = GetPawn()->GetActorLocation();
		FRotator BOSpawnRotation = GetPawn()->GetActorRotation();

		APawn* PrevPawn = GetPawn();
		UnPossess();

		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this; 

			APawn* NewPawn = World->SpawnActor<APawn>(PlayerClass, BOSpawnLocation, BOSpawnRotation, SpawnParams);
			if (NewPawn)
			{
				Possess(NewPawn);

				if (ABOCharacterPlayer* NewPlayer = Cast<ABOCharacterPlayer>(NewPawn))
				{
					NewPlayer->ChangeClass(SelectionClassData(InClassType));
				}
			}
		}

		PrevPawn->Destroy();
	}
}

void ABOLobbyPlayerController::ToggleSelectionWidget()
{
	LobbyWidget->ToggleSelectionClassWidget();
}

void ABOLobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	FInputModeGameAndUI GameOnly;
	SetInputMode(GameOnly);

	if (LobbyWidget = CreateWidget<UBOLobbyWidget>(GetWorld(), LobbyWidgetClass))
	{
		LobbyWidget->AddToViewport();
	}
}

UBOClassData* ABOLobbyPlayerController::SelectionClassData(const EClassType& InClassType)
{
	switch (InClassType)
	{
	case EClassType::Wraith:
		return WraithData;
	case EClassType::Aurora:
		return AuroraData;
	case EClassType::Kallari:
		return KallariData;
	case EClassType::Gideon:
		return GideonData;
	case EClassType::Terra:
		return TerraData;
	default:
		return WraithData;
	}
}
