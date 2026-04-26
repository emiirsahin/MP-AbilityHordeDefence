
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Objects/ActorSpawningAbilityInstance.h"
#include "ExplosionAreaAbilityInstance.generated.h"

class AFireballAbilityActor;

UCLASS()
class MPAHD_API UExplosionAreaAbilityInstance : public UActorSpawningAbilityInstance
{
	GENERATED_BODY()

public:
	friend class UFireballAbilityInstance;
	
protected:
	virtual void CommitActivation() override;
	
	virtual void Initialize(
		UAbilityDefinition* InAbilityDefinition,
		UAbilityComponent* InOwningAbilityComponent,
		int32 InSlotIndex) override;
	
	virtual AAbilityActorBase* SpawnAbilityActor() override;

	void SetOwningFireball(AFireballAbilityActor* InFireball);

	UPROPERTY()
	float BaseExplosionDamage = 50.f;

	UPROPERTY()
	float ExplosionRadius = 300.f;

	UPROPERTY()
	TObjectPtr<UCurveFloat> ExplosionDamageFalloffCurve;

	UPROPERTY()
	AFireballAbilityActor* OwningFireball;
};
