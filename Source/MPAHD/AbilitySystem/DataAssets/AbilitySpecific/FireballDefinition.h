
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/ActorSpawningAbilityDefinition.h"
#include "FireballDefinition.generated.h"

class UExplosionAreaAbilityDefinition;

UCLASS()
class MPAHD_API UFireballDefinition : public UActorSpawningAbilityDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability|Fireball")
	float ProjectileSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Internal|Explosion")
	TObjectPtr<UExplosionAreaAbilityDefinition> ExplosionAreaDefinition;
};

// DOES NOT DO DAMAGE. INTERNAL EXPLOSION AREA ABILITY DOES THE DAMAGE