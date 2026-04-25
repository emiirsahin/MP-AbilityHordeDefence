
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/AbilityDefinition.h"
#include "ActorSpawningAbilityDefinition.generated.h"

class AAbilityActorBase;

UCLASS()
class MPAHD_API UActorSpawningAbilityDefinition : public UAbilityDefinition
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Runtime")
	TSubclassOf<AAbilityActorBase> AbilityActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Runtime|Actor")
	FVector SpawnOffset = FVector::ZeroVector;
};
