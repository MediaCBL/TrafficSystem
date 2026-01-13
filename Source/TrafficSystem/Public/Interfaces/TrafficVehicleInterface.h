// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "UObject/Interface.h"
#include "TrafficVehicleInterface.generated.h"

UINTERFACE(Blueprintable)
class TRAFFICSYSTEM_API UTrafficVehicleInterface : public UInterface
{
	GENERATED_BODY()
};

class TRAFFICSYSTEM_API ITrafficVehicleInterface
{
	GENERATED_BODY()

public:
	/** Return true if this actor should block vehicles behind it */
	UFUNCTION(BlueprintNativeEvent, Category="Traffic")
	bool GetCanBlockTraffic() const;

	UFUNCTION(BlueprintNativeEvent)
	bool GetIsBlockedByTraffic() const;

	UFUNCTION(BlueprintNativeEvent)
	bool GetIsBlockedByLane() const;

	UFUNCTION(BlueprintNativeEvent)
	bool GetIsBlocked() const;

	UFUNCTION(BlueprintNativeEvent, Category="Traffic")
	void SetIsBlockedByTraffic(bool bIsBlocked);
	
	UFUNCTION(BlueprintNativeEvent, Category="Traffic")
	void SetIsBlockedByLane(bool bIsBlocked);
		
	UFUNCTION(BlueprintNativeEvent)
	void SetForcedMove(bool bAllowMove);
	
	UFUNCTION(BlueprintNativeEvent)
	float GetDistanceOnSpline() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetTrafficPriority() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetTrafficUniqueID() const;
};
