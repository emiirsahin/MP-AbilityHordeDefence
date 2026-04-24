
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UAbilityDefinition;
class UAbilityInstanceBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MPAHD_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateAbilityBySlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool AssignAbilityToSlot(int32 SlotIndex, UAbilityDefinition* AbilityDefinition);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	UAbilityInstanceBase* GetAbilityInstanceBySlot(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool IsValidAbilitySlot(int32 SlotIndex) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UAbilityDefinition>> InitialAbilityDefinitions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UAbilityInstanceBase>> AbilityInstances;

protected:
	void InitializeAbilities();
};