// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TrafficTypes.generated.h"

class USplineComponent;
class UBoxComponent;

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

UENUM(BlueprintType)
enum class ETrafficLightState : uint8
{
	Red,
	Yellow,
	Green
};

UENUM(BlueprintType)
enum class ETrafficLaneOrientation : uint8
{
	North UMETA(DisplayName="North"),
	South UMETA(DisplayName="South"),
	East UMETA(DisplayName="East"),
	West UMETA(DisplayName="West")
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

USTRUCT(BlueprintType)
struct FTrafficLane
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* StopVolume = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LightMesh = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* DynamicMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETrafficLightState CurrentState = ETrafficLightState::Red;
};

USTRUCT(BlueprintType)
struct FTrafficFollowerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USplineComponent* Spline = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 300.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceAlongSpline = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceOnSpline = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Priority = 0;            // Optional (main road > side road)
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 UniqueID = 0;            // Stable tie breaker
};
