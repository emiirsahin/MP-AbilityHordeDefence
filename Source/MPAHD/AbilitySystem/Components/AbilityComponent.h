
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UAbilityDefinition;
class UAbilityInstanceBase;

#define ABILITY_SLOT_COUNT 3

USTRUCT(BlueprintType)
struct FReplicatedAbilitySlot
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilityDefinition> AbilityDefinition = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentCooldown = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CooldownStartServerTime = -1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsBlocked = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReplicatedAbilitySlotsChanged);

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

	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnReplicatedAbilitySlotsChanged OnReplicatedAbilitySlotsChanged;
	
	UFUNCTION()
	void OnRep_AbilitySlots();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	float GetCooldownRemainingForSlot(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	float GetCooldownPercentForSlot(int32 SlotIndex) const;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UAbilityDefinition>> InitialAbilityDefinitions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UAbilityInstanceBase>> AbilityInstances;

	UPROPERTY(ReplicatedUsing=OnRep_AbilitySlots)
	TArray<FReplicatedAbilitySlot> ReplicatedAbilitySlots;

	void HandleReplicatedSlotsReplication();

protected:
	void InitializeAbilities();
};