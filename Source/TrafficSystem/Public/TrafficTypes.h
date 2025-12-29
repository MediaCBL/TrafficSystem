// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TrafficTypes.generated.h"

UENUM(BlueprintType)
enum class ETrafficRightOfWay : uint8
{
	Go     UMETA(DisplayName="Go"),
	Yield  UMETA(DisplayName="Yield"),
	Stop   UMETA(DisplayName="Stop")
};

UENUM(BlueprintType)
enum class ETrafficSignalState : uint8
{
	Red    UMETA(DisplayName="Red"),
	Yellow UMETA(DisplayName="Yellow"),
	Green  UMETA(DisplayName="Green"),

	// Optional pedestrian/walk support
	Walk       UMETA(DisplayName="Walk"),
	DontWalk   UMETA(DisplayName="Don't Walk")
};

USTRUCT(BlueprintType)
struct FTrafficMoveRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic")
	float DesiredSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic")
	float AcceptanceRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic")
	bool bStopAtDestination = true;
};
