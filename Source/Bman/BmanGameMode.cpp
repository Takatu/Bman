// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BmanGameMode.h"
#include "BmanPlayerController.h"
#include "BmanCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"


ABmanGameMode::ABmanGameMode()
	: NumTilesX(7)
	, NumTilesY(7)
	, TileSize(100.0f)
	, DestroyableSpawnChance(20)
	, RoundTime(60)
{
	// use our custom PlayerController class
	PlayerControllerClass = ABmanPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABmanGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(roundTimerHandle, this, &ABmanGameMode::OnRoundTimer, 1.0f, true);

	// create player 2
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	// receive damage events to end the round
	TArray<AActor*> pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DefaultPawnClass, pawns);
	for (auto pawn : pawns)
	{
		pawn->OnTakeAnyDamage.AddDynamic(this, &ABmanGameMode::OnTakeAnyDamge);
	}

	DamagedPlayers.Empty();
}

void ABmanGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	// generate level
	GenerateLevel();
}

void ABmanGameMode::GenerateLevel()
{
	if (!FloorTile.Get() || !WallTile.Get() || !DestroyableTile.Get())
		return;

	FTransform tform = FTransform::Identity;
	FVector offsetVectorX = FVector::ForwardVector * TileSize;
	FVector offsetVectorY = FVector::RightVector * TileSize;
	UWorld* world = GetWorld();

	for (int32 x = 0; x < NumTilesX; ++x)
	{
		for (int32 y = 0; y < NumTilesY; ++y)
		{
			// spawn floor only inside the "arena"
			if ((x > 0 && x < NumTilesX - 1) && (y > 0 && y < NumTilesY - 1) && (x % 2 == 1 || y % 2 == 1))
			{
				world->SpawnActor<AActor>(FloorTile, tform);

				// keep spawn area clean from destroyables
				if ((x > 2 || y > 2) && (x + 3 < NumTilesX || y + 3 < NumTilesY))
				{
					// random chance to spawn destroyables
					int32 randVal = FMath::RandRange(0, 100);
					if (randVal <= DestroyableSpawnChance)
						world->SpawnActor<AActor>(DestroyableTile, tform);
				}
			}
			else
			{
				world->SpawnActor<AActor>(WallTile, tform);
			}

			tform.AddToTranslation(offsetVectorY);
		}
		tform.AddToTranslation(-offsetVectorY * NumTilesY);
		tform.AddToTranslation(offsetVectorX);
	}

	// destroy existing player starts
	TArray<AActor*> resultActors;
	UGameplayStatics::GetAllActorsOfClass(world, APlayerStart::StaticClass(), resultActors);
	for (auto actor : resultActors)
		world->DestroyActor(actor);

	// spawn player start actors on oposit corners of the level
	FVector heightOffset(0.0f, 0.0f, 200.0f);
	tform.SetTranslation(offsetVectorY + offsetVectorX + heightOffset);
	world->SpawnActor<AActor>(APlayerStart::StaticClass(), tform);

	tform.SetTranslation(heightOffset + ((offsetVectorY * (NumTilesY - 2)) + (offsetVectorX * (NumTilesX - 2))));
	world->SpawnActor<AActor>(APlayerStart::StaticClass(), tform);
}

void ABmanGameMode::OnRoundTimer()
{
	// decrease round time by a second
	RoundTime--;

	// end round after time is up
	if (RoundTime < 0)
		EndRound();
}

void ABmanGameMode::OnTakeAnyDamge(AActor* DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (DamagedPlayers.Num() == 0)
	{
		// delay EndRound call by one tick to handle all damge before evaluating the win condition
		GetWorldTimerManager().SetTimerForNextTick(this, &ABmanGameMode::EndRound);
	}

	DamagedPlayers.AddUnique(DamagedActor);
}