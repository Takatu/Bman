// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BmanCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "UObject/ConstructorHelpers.h"

ABmanCharacter::ABmanCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;	
	
	// collect materials for diffrent players
	bodyMaterials.Add(ConstructorHelpers::FObjectFinderOptional<UMaterialInstanceConstant>(TEXT("MaterialInstanceConstant'/Game/Materials/MI_Player0Body'")).Get());
	bodyMaterials.Add(ConstructorHelpers::FObjectFinderOptional<UMaterialInstanceConstant>(TEXT("MaterialInstanceConstant'/Game/Materials/MI_Player1Body'")).Get());
}

void ABmanCharacter::ApplyColor(int32 playerId)
{
	check(bodyMaterials.Num() > playerId);
	GetMesh()->SetMaterial(0, bodyMaterials[playerId]);
}