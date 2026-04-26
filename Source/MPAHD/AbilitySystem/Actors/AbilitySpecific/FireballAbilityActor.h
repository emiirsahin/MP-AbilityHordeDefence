
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actors/AbilityActorBase.h"
#include "FireballAbilityActor.generated.h"

class UProjectileMovementComponent;

UCLASS()
class MPAHD_API AFireballAbilityActor : public AAbilityActorBase
{
	GENERATED_BODY()

public:
	AFireballAbilityActor();
	
	UFUNCTION(BlueprintCallable, Category = "Fireball|Movement")
	void SetProjectileSpeed(float InSpeed);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(BlueprintReadonly, Category = "Fireball|Movement")
	float ProjectileSpeed = 0.0f;

	void SpawnExplosionAreaActor();

	UFUNCTION()
	void OnProjectileStop(const FHitResult& ImpactResult);
};
