
#include "AbilityComponent.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/DataAssets/AbilityDefinition.h"
#include "AbilitySystem/Objects/AbilityInstanceBase.h"
#include "GameFramework/GameStateBase.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		InitializeAbilities();
	}
}

void UAbilityComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UAbilityInstanceBase* AbilityInstance : AbilityInstances)
	{
		if (!AbilityInstance)
		{
			continue;
		}

		AbilityInstance->TickAbility(DeltaTime);
	}
}

void UAbilityComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
	DOREPLIFETIME_CONDITION(UAbilityComponent, ReplicatedAbilitySlots, COND_OwnerOnly);
}

void UAbilityComponent::InitializeAbilities()
{
	AbilityInstances.SetNum(ABILITY_SLOT_COUNT);
	ReplicatedAbilitySlots.SetNum(ABILITY_SLOT_COUNT);
	
	for (int32 SlotIndex = 0; SlotIndex < AbilityInstances.Num(); ++SlotIndex)
	{
		if (!InitialAbilityDefinitions.IsValidIndex(SlotIndex))
		{
			continue;
		}

		UAbilityDefinition* AbilityDefinition = InitialAbilityDefinitions[SlotIndex];
		if (!AbilityDefinition)
		{
			continue;
		}

		AssignAbilityToSlot(SlotIndex, AbilityDefinition);
	}
}

bool UAbilityComponent::IsValidAbilitySlot(int32 SlotIndex) const
{
	return SlotIndex >= 0 && SlotIndex < ABILITY_SLOT_COUNT;
}

bool UAbilityComponent::AssignAbilityToSlot(int32 SlotIndex, UAbilityDefinition* AbilityDefinition)
{
	if (!IsValidAbilitySlot(SlotIndex))
	{
		return false;
	}

	if (!AbilityDefinition)
	{
		return false;
	}

	if (!AbilityDefinition->AbilityInstanceClass)
	{
		return false;
	}

	UAbilityInstanceBase* AbilityInstance = NewObject<UAbilityInstanceBase>(
		this,
		AbilityDefinition->AbilityInstanceClass);

	if (!AbilityInstance)
	{
		return false;
	}

	AbilityInstance->Initialize(AbilityDefinition, this, SlotIndex);
	AbilityInstances[SlotIndex] = AbilityInstance;

	FReplicatedAbilitySlot ReplicatedAbilitySlot;
	ReplicatedAbilitySlot.AbilityDefinition = AbilityDefinition;
	ReplicatedAbilitySlot.CurrentCooldown = AbilityDefinition->Cooldown;
	ReplicatedAbilitySlots[SlotIndex] = ReplicatedAbilitySlot;
	
	return true;
}

UAbilityInstanceBase* UAbilityComponent::GetAbilityInstanceBySlot(int32 SlotIndex) const
{
	if (!IsValidAbilitySlot(SlotIndex))
	{
		return nullptr;
	}

	return AbilityInstances[SlotIndex];
}

bool UAbilityComponent::TryActivateAbilityBySlot(int32 SlotIndex)
{
	UAbilityInstanceBase* AbilityInstance = GetAbilityInstanceBySlot(SlotIndex);
	if (!AbilityInstance)
	{
		return false;
	}

	if (!AbilityInstance->Activate())
	{
		return false;
	}

	if (!ReplicatedAbilitySlots.IsValidIndex(SlotIndex))
	{
		return false;
	}
	
	ReplicatedAbilitySlots[SlotIndex].CooldownStartServerTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	HandleReplicatedSlotsReplication();
	return true;
}

void UAbilityComponent::OnRep_AbilitySlots()
{
	HandleReplicatedSlotsReplication();
}

void UAbilityComponent::HandleReplicatedSlotsReplication()
{
	OnReplicatedAbilitySlotsChanged.Broadcast();
}

float UAbilityComponent::GetCooldownRemainingForSlot(int32 SlotIndex) const
{
	if (!ReplicatedAbilitySlots.IsValidIndex(SlotIndex))
	{
		return 0.0f;
	}

	const FReplicatedAbilitySlot& Slot = ReplicatedAbilitySlots[SlotIndex];

	if (Slot.CurrentCooldown <= 0.0f || Slot.CooldownStartServerTime < 0.0f)
	{
		return 0.0f;
	}

	const AGameStateBase* GameState = GetWorld() ? GetWorld()->GetGameState() : nullptr;
	if (!GameState)
	{
		return 0.0f;
	}

	const float ServerTime = GameState->GetServerWorldTimeSeconds();
	const float Elapsed = ServerTime - Slot.CooldownStartServerTime;

	return FMath::Max(0.0f, Slot.CurrentCooldown - Elapsed);
}

float UAbilityComponent::GetCooldownPercentForSlot(int32 SlotIndex) const
{
	if (!ReplicatedAbilitySlots.IsValidIndex(SlotIndex))
	{
		return 0.0f;
	}

	const float CurrentCooldown = ReplicatedAbilitySlots[SlotIndex].CurrentCooldown;
	if (CurrentCooldown <= 0.0f)
	{
		return 0.0f;
	}

	return GetCooldownRemainingForSlot(SlotIndex) / CurrentCooldown;
}