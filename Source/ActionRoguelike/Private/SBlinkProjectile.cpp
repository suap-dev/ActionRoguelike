// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlinkProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASBlinkProjectile::ASBlinkProjectile()
{
	ExplosionEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionEffectComp");
	ExplosionEffectComp->SetupAttachment(RootComponent);
	ExplosionEffectComp->SetAutoActivate(false);
}


void ASBlinkProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ASBlinkProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_MaxRangeReached, this,
	                                &ASBlinkProjectile::MaxRangeReached, TravelTime);
}


void ASBlinkProjectile::MaxRangeReached()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));

	Explode();
}

// Special type of explosion that also teleports the instigator to new location.
// It also automatically triggers in OnHit specified in Base class.
void ASBlinkProjectile::Explode_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));

	GetWorldTimerManager().ClearTimer(TimerHandle_MaxRangeReached);

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	EffectComp->DeactivateSystem();
	SpawnExplosionEmitter();

	// We do not intend to do anything with this handle after it's set, so it's not in the header file.
	FTimerHandle TimerHandle_TeleportInstigator;
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportInstigator, this,
	                                &ASBlinkProjectile::TeleportInstigator, TeleportDelay);
}


void ASBlinkProjectile::TeleportInstigator() const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));

	// GetInstigator()->SetActorLocation(GetActorLocation()); // Cleaner version below.

	if (AActor* ValidInstigator = GetInstigator(); ensure(ValidInstigator))
	{
		ValidInstigator->TeleportTo(GetActorLocation(), ValidInstigator->GetActorRotation());
	}
}
