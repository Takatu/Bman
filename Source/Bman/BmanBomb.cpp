// Fill out your copyright notice in the Description page of Project Settings.

#include "BmanBomb.h"
#include "BmanGameMode.h"
#include "BmanHelper.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ABmanBomb::ABmanBomb()
	: ExplosionRange(3)
	, TimeToLive(3.0f)
	, exploded(false)
{
 	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABmanBomb::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(explosionTimer, this, &ABmanBomb::Explode, TimeToLive, false);

	OnTakeAnyDamage.AddDynamic(this, &ABmanBomb::OnTakeAnyDamge);
}

void ABmanBomb::Explode()
{
	exploded = true;

	// spawn center explosion 
	GetWorld()->SpawnActor<AActor>(ExplosionClass, GetActorLocation(), FRotator::ZeroRotator);

	SpawnExplosions(FVector::ForwardVector);
	SpawnExplosions(-FVector::ForwardVector);
	SpawnExplosions(FVector::RightVector);
	SpawnExplosions(-FVector::RightVector);

	GetWorld()->DestroyActor(this);
}

// any damge callback
void ABmanBomb::OnTakeAnyDamge(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!exploded)
		Explode();
}

// spawn explosion actors
void ABmanBomb::SpawnExplosions(const FVector& dir)
{
	float tileSize = BmanHelper::GetTileSize(GetWorld());

	int32 range = ExplosionRange;
	FVector origin = GetActorLocation() + FVector(0.0f, 0.0f, 25.f); // make sure not to hit the floor
	FVector destination = origin + (dir * ExplosionRange * tileSize);

	// check for static hits and clamp explosion range
	FHitResult result;
	GetWorld()->LineTraceSingleByChannel(result, origin, destination, ECollisionChannel::ECC_WorldStatic);
	if (result.bBlockingHit)
	{
		range = FMath::FloorToInt(result.Distance / (tileSize));
		UGameplayStatics::ApplyDamage(result.Actor.Get(), 1.0f, nullptr, this, UDamageType::StaticClass());
	}

	for (int32 i = 1; i <= range; ++i)
	{
		FVector location = GetActorLocation() + (dir * i * tileSize);
		GetWorld()->SpawnActor<AActor>(ExplosionClass, location, FRotator::ZeroRotator);
	}
}


