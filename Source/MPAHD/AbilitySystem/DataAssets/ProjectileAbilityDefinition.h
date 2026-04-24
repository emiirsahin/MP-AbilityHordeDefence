
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/AbilityDefinition.h"
#include "ProjectileAbilityDefinition.generated.h"

class AAbilityActorBase;

UCLASS()
class MPAHD_API UProjectileAbilityDefinition : public UAbilityDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<AAbilityActorBase> AbilityActorClass;
};
