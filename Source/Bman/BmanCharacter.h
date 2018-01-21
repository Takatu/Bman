// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BmanCharacter.generated.h"

class UMaterialInstanceConstant;

UCLASS(Blueprintable)
class ABmanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABmanCharacter();

	// apply a color to the character by player Id
	void ApplyColorByPlayerID(int32 playerId);

private:
	TArray<UMaterialInstanceConstant*> bodyMaterials;
};

