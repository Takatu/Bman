// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 class for helper functions
 */
class BMAN_API BmanHelper
{
public:
	// returns the size of a tile in world units
	static float GetTileSize(UWorld* world);
};
