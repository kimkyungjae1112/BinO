// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BOCharacterBase.h"

ABOCharacterBase::ABOCharacterBase()
{
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

