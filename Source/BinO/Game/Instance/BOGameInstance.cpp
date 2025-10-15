// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Instance/BOGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "FindSessionsCallbackProxy.h"

UBOGameInstance::UBOGameInstance()
{

}

void UBOGameInstance::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("No SessionInterface"));
		return;
	}

	const FName SessionName(TEXT("MySessionName"));

	// 기존 세션 있으면 파괴 후 다시 생성 (Destroy 완료 델리게이트에서 재호출 권장)
	if (OnlineSessionInterface->GetNamedSession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Session already exists. Destroying first."));
		OnlineSessionInterface->DestroySession(SessionName);
		return;
	}

	// 델리게이트 바인딩(핸들 방식 권장하지만, 기존 방식이라도 Clear 먼저)
	OnlineSessionInterface->ClearOnCreateSessionCompleteDelegates(this);
	OnlineSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ThisClass::OnCreateSessionComplete);

	// 위의 권장 세팅 사용
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
	SessionSettings->bIsLANMatch = false;
	SessionSettings->NumPublicConnections = 4;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bUseLobbiesIfAvailable = true;

	const bool bReqOk = OnlineSessionInterface->CreateSession(0, SessionName, *SessionSettings);
	if (!bReqOk)
	{
		OnlineSessionInterface->ClearOnCreateSessionCompleteDelegates(this);
		UE_LOG(LogTemp, Error, TEXT("CreateSession() returned false immediately"));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("CreateSession() returned false"));
	}
}

void UBOGameInstance::FindGameSessions()
{
	if (!OnlineSessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find sessions, OnlineSessionInterface is not valid."));
		return;
	}

	// 새로운 세션 검색 객체 생성
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false; // LAN이 아닌 인터넷(스팀)에서 검색
	SessionSearch->MaxSearchResults = 20; // 최대 검색 결과 수
	SessionSearch->QuerySettings.Set(FName(TEXT("PRESENCESEARCH")), true, EOnlineComparisonOp::Equals);

	UE_LOG(LogTemp, Log, TEXT("Finding game sessions..."));

	// 델리게이트 바인딩 및 함수 호출
	OnlineSessionInterface->ClearOnFindSessionsCompleteDelegates(this);
	OnlineSessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ThisClass::OnFindSessionsComplete);
	OnlineSessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UBOGameInstance::JoinGameSession(const FBlueprintSessionResult& SessionResult)
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Joining a session..."));

	// 델리게이트 바인딩 및 함수 호출
	OnlineSessionInterface->ClearOnJoinSessionCompleteDelegates(this);
	OnlineSessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ThisClass::OnJoinSessionComplete);
	OnlineSessionInterface->JoinSession(0, "MySessionName", SessionResult.OnlineResult);

}

void UBOGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1500.f, FColor::Blue, FString::Printf(TEXT("Found subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString()));
		}
	}
}

void UBOGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Success Create Session : %s"), *SessionName.ToString()));
		}
		
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/_Game/Maps/PlayMapFirst"), true, TEXT("listen"));
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Faild Create Session")));
		}
	}
}

void UBOGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("OnFindSessionsComplete, Success: %d"), bWasSuccessful);

	if (bWasSuccessful && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Found %d sessions."), SessionSearch->SearchResults.Num());

		// Blueprint에서 사용하기 편하도록 FBlueprintSessionResult 배열로 변환
		TArray<FBlueprintSessionResult> BPResults;
		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			FBlueprintSessionResult BPResult;
			BPResult.OnlineResult = Result;
			BPResults.Add(BPResult);
		}

		// UI에 서버 목록이 업데이트되었다고 알림 (브로드캐스트)
		OnServerListUpdated.Broadcast(BPResults);
	}
	else
	{
		// 실패 시 빈 배열로 브로드캐스트
		OnServerListUpdated.Broadcast(TArray<FBlueprintSessionResult>());
	}


}
void UBOGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully joined session: %s"), *SessionName.ToString());

		// 서버 주소를 얻어와서 해당 서버로 이동 (ClientTravel)
		FString ConnectString;
		if (OnlineSessionInterface.IsValid() && OnlineSessionInterface->GetResolvedConnectString(SessionName, ConnectString))
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				PC->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to join session. Result: %d"), static_cast<int32>(Result));
	}
}