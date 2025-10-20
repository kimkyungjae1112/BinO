// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/BOSelectionClassWidget.h"
#include "Components/Button.h"
#include "Player/Controller/BOLobbyPlayerController.h"
#include "BODefine.h"

void UBOSelectionClassWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonWraith)
	{
		ButtonWraith->OnClicked.AddDynamic(this, &ThisClass::ChangeWraith);
	}

	if (ButtonAurora)
	{
		ButtonAurora->OnClicked.AddDynamic(this, &ThisClass::ChangeAurora);
	}

	if (ButtonKallari)
	{
		ButtonKallari->OnClicked.AddDynamic(this, &ThisClass::ChangeKallari);
	}

	if (ButtonGideon)
	{
		ButtonGideon->OnClicked.AddDynamic(this, &ThisClass::ChangeGideon);
	}

	if (ButtonTerra)
	{
		ButtonTerra->OnClicked.AddDynamic(this, &ThisClass::ChangeTerra);
	}
}

void UBOSelectionClassWidget::ChangeWraith()
{
	if (ABOLobbyPlayerController* PC = Cast<ABOLobbyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ChangeClass(EClassType::Wraith);
	}
}

void UBOSelectionClassWidget::ChangeAurora()
{
	if (ABOLobbyPlayerController* PC = Cast<ABOLobbyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ChangeClass(EClassType::Aurora);
	}
}

void UBOSelectionClassWidget::ChangeKallari()
{
	if (ABOLobbyPlayerController* PC = Cast<ABOLobbyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ChangeClass(EClassType::Kallari);
	}
}

void UBOSelectionClassWidget::ChangeGideon()
{
	if (ABOLobbyPlayerController* PC = Cast<ABOLobbyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ChangeClass(EClassType::Gideon);
	}
}

void UBOSelectionClassWidget::ChangeTerra()
{
	if (ABOLobbyPlayerController* PC = Cast<ABOLobbyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->ChangeClass(EClassType::Terra);
	}
}
