// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("PhysicsActor");
	// 	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);

	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
	ForceComp->ImpulseStrength = 150000.0f;
	ForceComp->Radius = 1500.0f;
	ForceComp->SetupAttachment(RootComponent);

}

void ASExplosiveBarrel::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	Explode();
}

void ASExplosiveBarrel::Explode()
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(
		-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	ForceComp->FireImpulse();
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

