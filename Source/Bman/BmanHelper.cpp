// Fill out your copyright notice in the Description page of Project Settings.

#include "BmanHelper.h"
#include "Engine/World.h"
#include "BmanGameMode.h"

float BmanHelper::GetTileSize(UWorld* world)
{
	float result = 100.0f;
	auto gameMode = Cast<ABmanGameMode>(world->GetAuthGameMode());
	if (gameMode)
		result = gameMode->TileSize;

	return result;
}
