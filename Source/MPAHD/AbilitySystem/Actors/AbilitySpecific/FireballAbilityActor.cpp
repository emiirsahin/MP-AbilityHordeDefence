
#include "AbilitySystem/Actors/AbilitySpecific/FireballAbilityActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFireballAbilityActor::AFireballAbilityActor()
{
	bReplicates = true;
	SetReplicatingMovement(true);
	PrimaryActorTick.bCanEverTick = true;
}

void AFireballAbilityActor::BeginPlay()
{
	Super::BeginPlay();

}

void AFireballAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	if (ProjectileSpeed > 0.0f)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		FVector NewLocation = CurrentLocation + (ForwardVector * ProjectileSpeed * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

void AFireballAbilityActor::SetProjectileSpeed(float InSpeed)
{
	ProjectileSpeed = InSpeed;
}