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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Traffic")
	bool GetCanBlockTraffic() const;

	/** Return true if this actor is blocked */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Traffic")
	bool GetIsBlocked() const;

	UFUNCTION(BlueprintImplementableEvent, Category="Traffic")
	void SetIsBlocked(bool bIsBlocked);
};
