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

	MovementComp->StopMovementImmediately();
	Explode();
}

void ASBlinkProjectile::Explode_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));
	
	SpawnExplosionEmitter();
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportInstigator, this,
									&ASBlinkProjectile::TeleportInstigator, TeleportDelay);
}


void ASBlinkProjectile::TeleportInstigator()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));

	GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();
}


void ASBlinkProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));

	GetWorldTimerManager().ClearTimer(TimerHandle_MaxRangeReached);
	Explode();
}
