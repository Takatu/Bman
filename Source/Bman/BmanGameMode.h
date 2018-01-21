// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BmanGameMode.generated.h"

/** 
 *
 ABmanGameMode generates the level and spawns the additional player.
 */
UCLASS(minimalapi)
class ABmanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABmanGameMode();

	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	
	// cllaback for player is taking damage
	UFUNCTION()
	void OnTakeAnyDamge(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// blueprint event for round end
	UFUNCTION(BlueprintImplementableEvent)
	void EndRound();

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

	// TODO: move to GameState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	int32 RoundTime; 

	// TODO: move to GameState
	UPROPERTY(BlueprintReadOnly, Category = Bman)
	TArray<AActor*> DamagedPlayers;

private:
	FTimerHandle roundTimerHandle;

	// generate level
	void GenerateLevel();
	// callback for round timer
	void OnRoundTimer();
};



