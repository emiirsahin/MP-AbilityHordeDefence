#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MPAHDGameState.generated.h"

UENUM(BlueprintType)
enum class EMPAHDMatchPhase : uint8
{
	Lobby         UMETA(DisplayName="Lobby"),
	MatchStarting UMETA(DisplayName="Match Starting"),
	InMatch       UMETA(DisplayName="In Match"),
	MatchEnded    UMETA(DisplayName="Match Ended")
};

UCLASS()
class MPAHD_API AMPAHDGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMPAHDGameState();

	UFUNCTION(BlueprintCallable)
	EMPAHDMatchPhase GetMatchPhase() const { return MatchPhase; }

	// Only called by server
	void SetMatchPhase(EMPAHDMatchPhase NewPhase);

protected:
	UPROPERTY(ReplicatedUsing=OnRep_MatchPhase, BlueprintReadOnly)
	EMPAHDMatchPhase MatchPhase = EMPAHDMatchPhase::Lobby;

	void HandleMatchPhaseChanged();
	
	UFUNCTION()
	void OnRep_MatchPhase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};