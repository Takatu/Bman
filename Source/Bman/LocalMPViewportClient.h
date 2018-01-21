// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "LocalMPViewportClient.generated.h"

/**
 * 
 ULocalMPViewportClient distributes the input to all players
 Source: https://wiki.unrealengine.com/Local_Multiplayer_Tips
 */
UCLASS()
class BMAN_API ULocalMPViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	ULocalMPViewportClient();

	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;	
};
