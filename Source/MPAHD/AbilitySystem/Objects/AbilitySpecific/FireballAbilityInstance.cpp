
#include "AbilitySystem/Objects/AbilitySpecific/FireballAbilityInstance.h"

#include "MPAHDCharacter.h"
#include "AbilitySystem/Actors/AbilitySpecific/FireballAbilityActor.h"
#include "AbilitySystem/DataAssets/AbilitySpecific/FireballDefinition.h"

void UFireballAbilityInstance::CommitActivation()
{
	Super::CommitActivation();

	SpawnAbilityActor();
}

void UFireballAbilityInstance::Initialize(UAbilityDefinition* InAbilityDefinition,
	UAbilityComponent* InOwningAbilityComponent, int32 InSlotIndex)
{
	Super::Initialize(InAbilityDefinition, InOwningAbilityComponent, InSlotIndex);

	if (UFireballDefinition* FireballDefinition = Cast<UFireballDefinition>(InAbilityDefinition))
	{
		ProjectileSpeed = FireballDefinition->ProjectileSpeed;
	}
}

AAbilityActorBase* UFireballAbilityInstance::SpawnAbilityActor()
{
	if (!AbilityActorClass || !OwningActor)
	{
		return nullptr;
	}

	UWorld* World = OwningActor->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	FVector CharacterForward = OwningActor->GetActorForwardVector();

	FVector SpawnLocation = OwningActor->GetActorLocation() + 
						  CharacterForward * SpawnOffset.X +
						  OwningActor->GetActorRightVector() * SpawnOffset.Y +
						  OwningActor->GetActorUpVector() * SpawnOffset.Z;

	FVector CameraForward = FVector::ZeroVector;
	if (AMPAHDCharacter* Character = Cast<AMPAHDCharacter>(OwningActor))
	{
		if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))
		{
			CameraForward = PC->PlayerCameraManager->GetCameraRotation().Vector();
		}
	}

	FRotator SpawnRotation = CameraForward.Rotation();
	
	AAbilityActorBase* SpawnedActor = World->SpawnActor<AAbilityActorBase>(
		AbilityActorClass,
		SpawnLocation,
		SpawnRotation
	);

	if (AFireballAbilityActor* FireballActor = Cast<AFireballAbilityActor>(SpawnedActor))
	{
		FireballActor->SetProjectileSpeed(ProjectileSpeed);
	}
	
	return SpawnedActor;
}
