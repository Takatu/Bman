// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BmanPlayerController.generated.h"

UCLASS()
class ABmanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABmanPlayerController();

protected:

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	// Input binding callbacks
	void OnDropBomb();
	void OnMoveForward(float val);
	void OnMoveRight(float val);

private:
	FVector moveDir;
};


