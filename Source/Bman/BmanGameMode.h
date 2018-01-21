// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BmanGameMode.generated.h"

UCLASS(minimalapi)
class ABmanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABmanGameMode();

	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman, meta = (ClampMin = "5", UIMin = "5"))
	int32 NumTilesX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman, meta = (ClampMin = "5", UIMin = "5"))
	int32 NumTilesY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TileSize;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	float DestroyableSpawnChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman)
	TSubclassOf<AActor> FloorTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman)
	TSubclassOf<AActor> WallTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bman)
	TSubclassOf<AActor> DestroyableTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	int32 RoundTime; // TODO: move to GameState

private:
	FTimerHandle roundTimerHandle;

	void GenerateLevel();
	void OnRoundTimer();

	void EndRound();
};



