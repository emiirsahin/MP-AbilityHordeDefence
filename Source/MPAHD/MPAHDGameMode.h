
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPAHDGameMode.generated.h"

UCLASS()
class MPAHD_API AMPAHDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMPAHDGameMode();

	UFUNCTION(BlueprintCallable)
	bool AreAllPlayersReady() const;

	void TryStartMatch();
};