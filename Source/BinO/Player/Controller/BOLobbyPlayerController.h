// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BODefine.h"
#include "BOLobbyPlayerController.generated.h"

class UBOClassData;
class UBOLobbyWidget;

UCLASS()
class BINO_API ABOLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBOLobbyWidget> LobbyWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UBOLobbyWidget> LobbyWidget;

protected:
	UPROPERTY(EditAnywhere, Category = "Player | Class")
	TSubclassOf<APawn> PlayerClass;

	UPROPERTY(EditAnywhere, Category = "Player | Data")
	TObjectPtr<UBOClassData> WraithData;

	UPROPERTY(EditAnywhere, Category = "Player | Data")
	TObjectPtr<UBOClassData> AuroraData;

	UPROPERTY(EditAnywhere, Category = "Player | Data")
	TObjectPtr<UBOClassData> KallariData;

	UPROPERTY(EditAnywhere, Category = "Player | Data")
	TObjectPtr<UBOClassData> GideonData;

	UPROPERTY(EditAnywhere, Category = "Player | Data")
	TObjectPtr<UBOClassData> TerraData;

public:
	void ChangeClass(const EClassType& InClassType);

	void ToggleSelectionWidget();

protected:
	virtual void BeginPlay() override;

private:
	UBOClassData* SelectionClassData(const EClassType& InClassType);
};
