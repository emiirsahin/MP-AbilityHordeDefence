
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MPAHDPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MPAHD_API AMPAHDPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMPAHDPlayerState();

	UFUNCTION(BlueprintCallable)
	bool IsReady() const { return bReady; }

	// Server sets this
	void SetReady_Server(bool bNewReady);

protected:
	UPROPERTY(ReplicatedUsing=OnRep_Ready)
	bool bReady = false;

	UFUNCTION()
	void OnRep_Ready();

	void HandleReadyChanged();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
