// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BmanCharacter.generated.h"

class UMaterialInstanceConstant;

/**
 *
 ABmanCharacter is the pawn class of Bman
 */
UCLASS(Blueprintable)
class ABmanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABmanCharacter();

	// apply a color to the character by controller Id
	void ApplyColor(int32 controllerId);

private:
	TArray<UMaterialInstanceConstant*> bodyMaterials;
};

