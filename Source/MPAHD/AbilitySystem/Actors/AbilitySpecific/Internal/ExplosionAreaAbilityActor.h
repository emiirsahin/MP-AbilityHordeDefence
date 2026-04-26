
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actors/AbilityActorBase.h"
#include "ExplosionAreaAbilityActor.generated.h"

class USphereComponent;
class UCurveFloat;

UCLASS()
class MPAHD_API AExplosionAreaAbilityActor : public AAbilityActorBase
{
	GENERATED_BODY()

public:
	AExplosionAreaAbilityActor();

	void InitializeExplosion(
		float InRadius,
		float InDamage,
		UCurveFloat* InFalloffCurve
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Explosion")
	TObjectPtr<USphereComponent> ExplosionSphere;

	UPROPERTY(BlueprintReadOnly, Category="Explosion")
	float ExplosionRadius = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="Explosion")
	float ExplosionDamage = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="Explosion")
	TObjectPtr<UCurveFloat> ExplosionDamageFalloffCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Explosion|Debug")
	TObjectPtr<UStaticMeshComponent> DebugSphereMesh;

	void ApplyExplosionDamage();

	float CalculateDamageAtDistance(float Distance) const;
};