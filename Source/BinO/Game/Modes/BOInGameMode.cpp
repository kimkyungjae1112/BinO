// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Modes/BOInGameMode.h"
#include "Game/Session/BOGameSession.h"

ABOInGameMode::ABOInGameMode()
{
	GameSessionClass = ABOGameSession::StaticClass();
}
