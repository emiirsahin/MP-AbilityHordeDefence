
#include "AbilitySystem/Actors/AbilitySpecific/FireballAbilityActor.h"
#include "AbilitySystem/Objects/AbilitySpecific/FireballAbilityInstance.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFireballAbilityActor::AFireballAbilityActor()
{
	bReplicates = true;
	SetReplicatingMovement(true);

	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = 0.0f;
		ProjectileMovement->MaxSpeed = 0.0f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = false;
		ProjectileMovement->ProjectileGravityScale = 0.0f;
	}
}

void AFireballAbilityActor::BeginPlay()
{
	Super::BeginPlay();

	if (!ProjectileMovement)
	{
		ProjectileMovement = FindComponentByClass<UProjectileMovementComponent>();
	}

	if (ProjectileMovement)
	{
		ProjectileMovement->OnProjectileStop.AddDynamic(this, &AFireballAbilityActor::OnProjectileStop);
	}
}

void AFireballAbilityActor::SetProjectileSpeed(float InSpeed)
{
    
	ProjectileSpeed = InSpeed;
    
	if (!ProjectileMovement)
	{
		return;
	}

	ProjectileMovement->InitialSpeed = InSpeed;
	ProjectileMovement->MaxSpeed = InSpeed;

	const FVector Direction = GetActorForwardVector();
	ProjectileMovement->Velocity = Direction * InSpeed;
	
	ProjectileMovement->Activate(true);
}

void AFireballAbilityActor::OnProjectileStop(const FHitResult& ImpactResult)
{
	if (HasAuthority())
	{
		SpawnExplosionAreaActor();
	}
}

void AFireballAbilityActor::SpawnExplosionAreaActor()
{
	if (SourceAbilityInstance)
	{
		if (UFireballAbilityInstance* FireballInstance = Cast<UFireballAbilityInstance>(SourceAbilityInstance))
		{
			FireballInstance->SpawnExplosionArea(this);
		}
	}

	
	Destroy();
}
