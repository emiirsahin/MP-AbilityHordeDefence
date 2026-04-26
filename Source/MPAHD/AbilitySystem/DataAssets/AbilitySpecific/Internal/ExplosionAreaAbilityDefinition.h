
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/ActorSpawningAbilityDefinition.h"
#include "ExplosionAreaAbilityDefinition.generated.h"

UCLASS()
class MPAHD_API UExplosionAreaAbilityDefinition : public UActorSpawningAbilityDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability|Explosion")
	float BaseExplosionDamage = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability|Explosion")
	float ExplosionRadius = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability|Explosion")
	TObjectPtr<UCurveFloat> ExplosionDamageFalloffCurve;
};
