#include "AbilitySystem/Actors/AbilitySpecific/Internal/ExplosionAreaAbilityActor.h"

#include "Components/SphereComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"

AExplosionAreaAbilityActor::AExplosionAreaAbilityActor()
{
	bReplicates = true;
	SetReplicatingMovement(false);

	PrimaryActorTick.bCanEverTick = false;

	ExplosionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
	SetRootComponent(ExplosionSphere);

	ExplosionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExplosionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	ExplosionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ExplosionSphere->SetGenerateOverlapEvents(true);

	DebugSphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugSphereMesh"));
	DebugSphereMesh->SetupAttachment(RootComponent);
	DebugSphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DebugSphereMesh->SetHiddenInGame(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(
		TEXT("/Engine/BasicShapes/Sphere.Sphere")
	);

	if (SphereMesh.Succeeded())
	{
		DebugSphereMesh->SetStaticMesh(SphereMesh.Object);
	}

	DebugSphereMesh->SetIsReplicated(true);
}

void AExplosionAreaAbilityActor::InitializeExplosion(
	float InRadius,
	float InDamage,
	UCurveFloat* InFalloffCurve
)
{
	ExplosionRadius = InRadius;
	ExplosionDamage = InDamage;
	ExplosionDamageFalloffCurve = InFalloffCurve;

	if (ExplosionSphere)
	{
		ExplosionSphere->SetSphereRadius(ExplosionRadius, true);
	}

	if (DebugSphereMesh)
	{
		const float MeshDefaultRadius = 50.0f;
		const float Scale = ExplosionRadius / MeshDefaultRadius;

		DebugSphereMesh->SetRelativeScale3D(FVector(Scale));
	}

	if (HasAuthority())
	{
		ApplyExplosionDamage();
	}
}

void AExplosionAreaAbilityActor::ApplyExplosionDamage()
{
	if (!ExplosionSphere || ExplosionRadius <= 0.0f || ExplosionDamage <= 0.0f)
	{
		return;
	}

	TArray<AActor*> OverlappingActors;
	ExplosionSphere->GetOverlappingActors(OverlappingActors);

	const FVector ExplosionCenter = GetActorLocation();

	for (AActor* TargetActor : OverlappingActors)
	{
		if (!IsValid(TargetActor) || TargetActor == GetOwner())
		{
			continue;
		}

		const float Distance = FVector::Dist(ExplosionCenter, TargetActor->GetActorLocation());
		const float FinalDamage = CalculateDamageAtDistance(Distance);

		if (FinalDamage <= 0.0f)
		{
			continue;
		}

		UGameplayStatics::ApplyDamage(
			TargetActor,
			FinalDamage,
			GetInstigatorController(),
			this,
			nullptr
		);
	}
}

float AExplosionAreaAbilityActor::CalculateDamageAtDistance(float Distance) const
{
	if (ExplosionRadius <= 0.0f)
	{
		return 0.0f;
	}

	const float NormalizedDistance = FMath::Clamp(Distance / ExplosionRadius, 0.0f, 1.0f);

	float FalloffMultiplier = 1.0f - NormalizedDistance;

	if (ExplosionDamageFalloffCurve)
	{
		FalloffMultiplier = ExplosionDamageFalloffCurve->GetFloatValue(NormalizedDistance);
	}

	FalloffMultiplier = FMath::Clamp(FalloffMultiplier, 0.0f, 1.0f);

	return ExplosionDamage * FalloffMultiplier;
}