// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	// 	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	// 	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// 	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->bRotationFollowsVelocity = true;	// this happens each frame
	MovementComp->bInitialVelocityInLocalSpace = true;

	MovementComp->InitialSpeed = InitialSpeed;	// default is set in header
	InitialLifeSpan = 5.0f;

	MovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

