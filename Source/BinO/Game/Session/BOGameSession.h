// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "BOGameSession.generated.h"

UCLASS()
class BINO_API ABOGameSession : public AGameSession
{
	GENERATED_BODY()

protected:
	virtual FString ApproveLogin(const FString& Options) override;
};
