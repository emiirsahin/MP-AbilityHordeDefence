
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/ActorSpawningAbilityDefinition.h"
#include "FireballDefinition.generated.h"

UCLASS()
class MPAHD_API UFireballDefinition : public UActorSpawningAbilityDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability|Runtime|Fireball")
	float ProjectileSpeed = 100.f;
};

// DOES NOT DO DAMAGE. INTERNAL EXPLOSION AREA ABILITY DOES THE DAMAGE