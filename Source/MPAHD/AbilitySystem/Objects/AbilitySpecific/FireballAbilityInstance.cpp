
#include "AbilitySystem/Objects/AbilitySpecific/FireballAbilityInstance.h"
#include "MPAHDCharacter.h"
#include "AbilitySystem/Actors/AbilitySpecific/FireballAbilityActor.h"
#include "AbilitySystem/DataAssets/AbilitySpecific/FireballDefinition.h"
#include "AbilitySystem/DataAssets/AbilitySpecific/Internal/ExplosionAreaAbilityDefinition.h"
#include "Internal/ExplosionAreaAbilityInstance.h"

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
		ExplosionAreaAbilityDefinition = FireballDefinition->ExplosionAreaDefinition;
	}

	InitializeInternalAbilities();
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
	
	AFireballAbilityActor* FireballActor = World->SpawnActor<AFireballAbilityActor>(
		AbilityActorClass,
		SpawnLocation,
		SpawnRotation
	);
	
	if (FireballActor)
	{
		FireballActor->SetProjectileSpeed(ProjectileSpeed);
	}

	FireballActor->InitializeAbilityActor(
	OwningActor,
	OwningAbilityComponent,
	this);
	
	return FireballActor;
}

void UFireballAbilityInstance::SpawnExplosionArea(AFireballAbilityActor* InFireballActor)
{
	if (!ExplosionAreaAbilityInstance)
	{
		return;
	}
	
	ExplosionAreaAbilityInstance->SetOwningFireball(InFireballActor);
	ExplosionAreaAbilityInstance->CommitActivation();
}

void UFireballAbilityInstance::InitializeInternalAbilities()
{
	if (!ExplosionAreaAbilityDefinition)
	{
		return;
	}

	if (!ExplosionAreaAbilityDefinition->AbilityInstanceClass)
	{
		return;
	}

	ExplosionAreaAbilityInstance = NewObject<UExplosionAreaAbilityInstance>(
		this,
		ExplosionAreaAbilityDefinition->AbilityInstanceClass);

	if (!ExplosionAreaAbilityInstance)
	{
		return;
	}

	ExplosionAreaAbilityInstance->Initialize(ExplosionAreaAbilityDefinition, GetOwningAbilityComponent(), 0);
}
