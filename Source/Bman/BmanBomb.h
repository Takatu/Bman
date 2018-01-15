// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BmanBomb.generated.h"

UCLASS()
class BMAN_API ABmanBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABmanBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Explode();

	UFUNCTION()
	void OnTakeAnyDamge(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	int32 ExplosionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	float TimeToLive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bman)
	TSubclassOf<AActor> ExplosionClass;

private:
	void SpawnExplosions(const FVector& dir);

	FTimerHandle explosionTimer;
	bool exploded;
};
