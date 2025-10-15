// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/BOServerRowWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OnlineSessionSettings.h"
#include "Game/Instance/BOGameInstance.h"

void UBOServerRowWidget::Setup(const FBlueprintSessionResult& InSessionResult)
{
	SessionResult = InSessionResult;

	if (ServerNameText)
	{
		// 세션 설정에서 서버 이름 가져오기
		FString ServerName;
		// CreateSession 시점에 SESSION_NAME_KEY로 저장된 이름을 찾습니다.
		// 만약 없다면 세션 ID를 대신 표시합니다.
		if (SessionResult.OnlineResult.Session.SessionSettings.Get(FName("SESSION_NAME_KEY"), ServerName))
		{
			ServerNameText->SetText(FText::FromString(ServerName));
		}
		else
		{
			ServerNameText->SetText(FText::FromString(SessionResult.OnlineResult.GetSessionIdStr()));
		}
	}

	if (PlayerCountText)
	{
		const FOnlineSessionSearchResult& SearchResult = SessionResult.OnlineResult;
		int32 MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
		int32 CurrentPlayers = MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
		FString PlayerCountStr = FString::Printf(TEXT("%d / %d"), CurrentPlayers, MaxPlayers);
		PlayerCountText->SetText(FText::FromString(PlayerCountStr));
	}
}

void UBOServerRowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::OnJoinButtonClicked);
	}
}

void UBOServerRowWidget::OnJoinButtonClicked()
{
	if (UBOGameInstance* GI = GetGameInstance<UBOGameInstance>())
	{
		GI->JoinGameSession(SessionResult);
	}
}