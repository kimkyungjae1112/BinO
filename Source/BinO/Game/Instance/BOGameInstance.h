// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BOGameInstance.generated.h"

struct FBlueprintSessionResult;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnServerListUpdated, const TArray<FBlueprintSessionResult>&)

UCLASS()
class BINO_API UBOGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/* 서버 목록이 업데이트되면 UI에 알리기 위한 델리게이트 */
	FOnServerListUpdated OnServerListUpdated;
	
	IOnlineSessionPtr OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

public:
	UBOGameInstance();

public:
	void CreateGameSession();
	void FindGameSessions();
	void JoinGameSession(const FBlueprintSessionResult& SessionResult);


protected:
	virtual void Init() override;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

};
