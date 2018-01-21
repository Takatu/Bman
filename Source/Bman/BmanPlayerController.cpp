// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BmanPlayerController.h"
#include "BmanCharacter.h"
#include "BmanPlayerState.h"
#include "BmanHelper.h"
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

void ABmanPlayerController::SetPawn(APawn* pawn)
{
	Super::SetPawn(pawn);
	
	// apply color to the player character by its controller id
	auto bmanChar = Cast<ABmanCharacter>(pawn);
	if (bmanChar)
		bmanChar->ApplyColor(UGameplayStatics::GetPlayerControllerID(this));
}

void ABmanPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	auto pawn = Cast<ABmanCharacter>(GetPawn());
	if (pawn)
	{
		pawn->AddMovementInput(moveDir);
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
	auto playerState = Cast<ABmanPlayerState>(GetPawn()->PlayerState);
	if (!playerState)
		return;
	
	if (playerState->MaxBombCount > playerState->BombCount)
	{
		float tileSize = BmanHelper::GetTileSize(GetWorld());

		// increase bomp count
		playerState->BombCount++;
		FTransform tform = GetPawn()->GetActorTransform();
		FVector translation = tform.GetTranslation();
		
		// Snap to grid
		translation.X = FMath::RoundToFloat(translation.X / tileSize) * tileSize;
		translation.Y = FMath::RoundToFloat(translation.Y / tileSize) * tileSize;
		translation.Z = 0.0f; // FIXME find ground level by raycast
		tform.SetTranslation(translation);

		// spawn bomb actor
		FActorSpawnParameters params;
		params.Instigator = this->GetPawn();
		auto bomb = GetWorld()->SpawnActor<AActor>(playerState->BombClass, tform, params);

		// register bomb destroyed callback
		bomb->OnDestroyed.AddDynamic(this, &ABmanPlayerController::OnBombDestroyed);
	}
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

void ABmanPlayerController::OnBombDestroyed(AActor* destroyedActor)
{
	auto playerState = Cast<ABmanPlayerState>(GetPawn()->PlayerState);
	if (playerState)
		playerState->BombCount--;
}
