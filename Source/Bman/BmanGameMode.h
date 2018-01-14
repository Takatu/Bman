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
};



