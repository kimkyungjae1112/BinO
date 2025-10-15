// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/BOLobbyWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Game/Instance/BOGameInstance.h"
#include "UI/Lobby/BOServerRowWidget.h"

void UBOLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateGameButton)
	{
		CreateGameButton->OnClicked.AddDynamic(this, &ThisClass::CreateGame);
	}

	if (FindGameButton)
	{
		FindGameButton->OnClicked.AddDynamic(this, &ThisClass::FindGame);
	}

	if (UBOGameInstance* GI = GetWorld()->GetGameInstance<UBOGameInstance>())
	{
		GI->OnServerListUpdated.AddUObject(this, &ThisClass::OnServerListUpdated);
	}
}

void UBOLobbyWidget::CreateGame()
{
	if (UBOGameInstance* GI = GetWorld()->GetGameInstance<UBOGameInstance>())
	{
		GI->CreateGameSession();
	}
}

void UBOLobbyWidget::FindGame()
{
	if (UBOGameInstance* GI = GetWorld()->GetGameInstance<UBOGameInstance>())
	{
		GI->FindGameSessions();
	}
}

void UBOLobbyWidget::OnServerListUpdated(const TArray<FBlueprintSessionResult>& ServerList)
{
	if (!ServerListContainer) return;

	// 기존 목록 초기화
	ServerListContainer->ClearChildren();

	UE_LOG(LogTemp, Log, TEXT("Updating UI with %d servers."), ServerList.Num());

	for (const FBlueprintSessionResult& Result : ServerList)
	{
		UBOServerRowWidget* ServerRow = CreateWidget<UBOServerRowWidget>(this, ServerRowWidgetClass);
		if (ServerRow)
		{
			ServerRow->Setup(Result);
			ServerListContainer->AddChild(ServerRow);
		}
	}
}
