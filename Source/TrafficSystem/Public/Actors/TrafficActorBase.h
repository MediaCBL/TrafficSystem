// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TrafficVehicleInterface.h"
#include "TrafficActorBase.generated.h"

struct FTrafficFollowerInfo;
class UTrafficSplineFollowerComponent;
class UTrafficFrontSensorComponent;

UCLASS()
class TRAFFICSYSTEM_API ATrafficActorBase : public AActor, public ITrafficVehicleInterface
{
	GENERATED_BODY()

public:
	ATrafficActorBase();
	
	UFUNCTION()
	void OnTrafficBlockStateChanged(bool bIsBlocked, AActor* TrafficBlocker);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTrafficSplineFollowerComponent> SplineFollowerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTrafficFrontSensorComponent> TrafficFrontSensorComponent;

	virtual void SetForcedMove_Implementation(bool bAllowMove) override;

	virtual void SetIsBlockedByTraffic_Implementation(bool bIsBlocked) override;

	virtual void SetIsBlockedByLane_Implementation(bool bIsBlocked) override;

	virtual bool GetCanBlockTraffic_Implementation() const override;

	virtual float GetDistanceOnSpline_Implementation() const override;

	virtual int32 GetTrafficPriority_Implementation() const override;

	virtual int32 GetTrafficUniqueID_Implementation() const override;
	
	virtual bool GetIsBlockedByTraffic_Implementation() const override;
	
	virtual bool GetIsBlockedByLane_Implementation() const override;
	
	virtual bool GetIsBlocked_Implementation() const override;
	
	virtual bool GetIsBlockedByActor_Implementation(const AActor* Actor) const override;

protected:
	UPROPERTY(BlueprintReadWrite, Category="Traffic")
	bool bIsBlockedByTraffic = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Traffic")
	bool bIsBlockedByLane = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic")
	bool bCanBlockTraffic;
};
