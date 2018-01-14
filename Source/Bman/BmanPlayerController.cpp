// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BmanPlayerController.h"
#include "BmanCharacter.h"
#include "Kismet/GameplayStatics.h"

// Input actions
namespace {
	const FString DROP_BOMB_ACTION = "DropBomb";
	const FString MOVE_FORWARD_ACTION = "MoveForward";
	const FString MOVE_RIGHT_ACTION = "MoveRight";
	const FString ACTION_FORMAT_STRING = TEXT("P{0}_{1}");
}

ABmanPlayerController::ABmanPlayerController()
{
}

void ABmanPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	auto pawn = static_cast<ABmanCharacter*>(GetPawn());
	if (pawn)
	{
		pawn->AddMovementInput(moveDir);
		pawn->ApplyColorByPlayerID(UGameplayStatics::GetPlayerControllerID(this));
	}

	moveDir = FVector::ZeroVector;
}

void ABmanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// build input binding names for player by controller id
	int32 controllerId = UGameplayStatics::GetPlayerControllerID(this);
	FName dropBombAction(*FString::Format(*ACTION_FORMAT_STRING, { controllerId, DROP_BOMB_ACTION }));
	FName moveForwardAction(*FString::Format(*ACTION_FORMAT_STRING, { controllerId, MOVE_FORWARD_ACTION }));
	FName moveRightAction(*FString::Format(*ACTION_FORMAT_STRING, { controllerId, MOVE_RIGHT_ACTION }));

	// bind input actions
	InputComponent->BindAction(dropBombAction, EInputEvent::IE_Pressed, this, &ABmanPlayerController::OnDropBomb);

	// bind input axis
	InputComponent->BindAxis(moveForwardAction, this, &ABmanPlayerController::OnMoveForward);
	InputComponent->BindAxis(moveRightAction, this, &ABmanPlayerController::OnMoveRight);
}

void ABmanPlayerController::OnDropBomb()
{

}

void ABmanPlayerController::OnMoveForward(float val)
{
	if (FMath::IsNearlyZero(val))
		return;

	moveDir = FVector::ForwardVector;
	moveDir *= FMath::IsNegativeFloat(val) ? -1.f : 1.f;
}

void ABmanPlayerController::OnMoveRight(float val)
{
	if (FMath::IsNearlyZero(val))
		return;

	moveDir = FVector::RightVector;
	moveDir *= FMath::IsNegativeFloat(val) ? -1.f : 1.f;
}
