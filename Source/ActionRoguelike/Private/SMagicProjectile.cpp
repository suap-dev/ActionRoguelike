// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
	: Super()
{
// 	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
	MovementComp->InitialSpeed = 1000.f;
	InitialLifeSpan = 5.0f;

}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void ASMagicProjectile::OnHit(
// 	UPrimitiveComponent* HitComponent,
// 	AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp,
// 	FVector NormalImpulse,
// 	const FHitResult& Hit)
// {
// 	check(GEngine);
// 	GEngine->AddOnScreenDebugMessage(
// 		-1, 15.0f, FColor::Yellow, TEXT("Projectile OnHit triggered."));
// 
// 	// 	Destroy();
// }

