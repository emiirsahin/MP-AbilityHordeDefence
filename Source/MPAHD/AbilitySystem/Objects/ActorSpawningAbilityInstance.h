
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Objects/AbilityInstanceBase.h"
#include "ActorSpawningAbilityInstance.generated.h"

class AAbilityActorBase;

UCLASS()
class MPAHD_API UActorSpawningAbilityInstance : public UAbilityInstanceBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Ability|Actor")
	TSubclassOf<AAbilityActorBase> GetAbilityActorClass() const { return AbilityActorClass; }

protected:
	virtual void Initialize(
		UAbilityDefinition* InAbilityDefinition,
		UAbilityComponent* InOwningAbilityComponent,
		int32 InSlotIndex) override;

	virtual AAbilityActorBase* SpawnAbilityActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Actor")
	FVector SpawnOffset = FVector::ZeroVector;

	TSubclassOf<AAbilityActorBase> AbilityActorClass = nullptr;
};
