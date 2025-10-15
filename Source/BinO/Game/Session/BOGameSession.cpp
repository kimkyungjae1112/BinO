// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Session/BOGameSession.h"

FString ABOGameSession::ApproveLogin(const FString& Options)
{
    FString ErrorMessage = Super::ApproveLogin(Options);

    return FString();
}
