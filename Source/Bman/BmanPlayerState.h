// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BmanBomb.h"
#include "BmanPlayerState.generated.h"

/**
 *
 ABmanPlayerState keeps player related data
 */
UCLASS()
class BMAN_API ABmanPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	TSubclassOf<AActor> BombClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bman)
	int32 BombCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	int32 MaxBombCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	int32 BombExposionRange;
};
