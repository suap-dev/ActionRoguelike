// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlinkProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASBlinkProjectile::ASBlinkProjectile()
{
	ExplosionEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionEffectComp");
	ExplosionEffectComp->SetupAttachment(RootComponent);
	ExplosionEffectComp->SetAutoActivate(false);
}


void ASBlinkProjectile::PostInitializeComponents()
{
	// Remember to call the parent function!
	Super::PostInitializeComponents();

	// SphereComp->OnComponentHit.AddDynamic(this, &ASBlinkProjectile::OnHit);
}


void ASBlinkProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_MaxRangeReached, this,
	                                &ASBlinkProjectile::MaxRangeReached, TravelTime);
}


void ASBlinkProjectile::MaxRangeReached()
{
	UE_LOG(LogTemp, Log, TEXT("BlinkProjectile -> MaxRangeReached"));

	MovementComp->StopMovementImmediately();

	SpawnExplosionEmitter();
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportInstigator, this,
	                                &ASBlinkProjectile::TeleportInstigator, TeleportDelay);
}


void ASBlinkProjectile::TeleportInstigator()
{
	UE_LOG(LogTemp, Log, TEXT("BlinkProjectile -> InstigatorTeleported"));

	GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();
}


void ASBlinkProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("BlinkProjectile -> Hit"));

	GetWorldTimerManager().ClearTimer(TimerHandle_MaxRangeReached);

	SpawnExplosionEmitter();
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportInstigator, this,
	                                &ASBlinkProjectile::TeleportInstigator, TeleportDelay);
}
