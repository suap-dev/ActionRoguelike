// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlinkProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASBlinkProjectile::ASBlinkProjectile() : Super()
{
	ExplosionEffectComp =
		CreateDefaultSubobject<UParticleSystemComponent>("ExplosionEffectComp");
	ExplosionEffectComp->SetupAttachment(RootComponent);
	ExplosionEffectComp->SetAutoActivate(false);

}


void ASBlinkProjectile::PostInitializeComponents()
{
	// Remember to call the parent function!
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ASBlinkProjectile::OnHit);

}


void ASBlinkProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		TimerHandle_Explosion, this,
		&ASBlinkProjectile::Explode, ExplosionDelay);

}


void ASBlinkProjectile::Explode()
{
	MovementComp->StopMovementImmediately();
	ExplosionEffectComp->Activate(true);

	GetWorldTimerManager().SetTimer(
		TimerHandle_Teleport, this,
		&ASBlinkProjectile::Teleport, TeleportDelay);

}


void ASBlinkProjectile::Teleport()
{
	UE_LOG(LogTemp, Log, TEXT("BLINK!"));
	GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();

}


void ASBlinkProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Hit."));
	GetWorldTimerManager().ClearTimer(TimerHandle_Explosion);
	Explode();

}
