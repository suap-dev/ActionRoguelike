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
	// MeshComp->SetCollisionProfileName("PhysicsActor");
	// MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	//
	// MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);

	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	// 	ForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	ForceComp->ImpulseStrength = 150000.0f;
	ForceComp->Radius = 1500.0f;
	// ForceComp->bImpulseVelChange = true; // Impulse velocity scales with objects mass
	ForceComp->SetAutoActivate(false);
	ForceComp->SetupAttachment(RootComponent);
}

// this is called BEFORE BeginPlay, after the constructor.
void ASExplosiveBarrel::PostInitializeComponents()
{
	// Remember to call the parent function!
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);
}

void ASExplosiveBarrel::OnHit([[maybe_unused]] UPrimitiveComponent* HitComponent,
                              [[maybe_unused]] AActor* OtherActor,
                              [[maybe_unused]] UPrimitiveComponent* OtherComp,
                              [[maybe_unused]] FVector NormalImpulse,
                              [[maybe_unused]] const FHitResult& Hit)
{
	StartDissolving();
	GetWorldTimerManager().SetTimer(TimerHandle_Explosion, this,
	                                &ASExplosiveBarrel::Explode, 0.05f);

	GetWorldTimerManager().SetTimer(TimerHandle_Destruction, this,
	                                &ASExplosiveBarrel::Destroy, 1.0f);
}

void ASExplosiveBarrel::Explode() const
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	                                 TEXT("Barrel exploded!"));

	ForceComp->FireImpulse();
}

void ASExplosiveBarrel::Destroy()
{
	Super::Destroy();
}

void ASExplosiveBarrel::StartDissolving()
{
	bIsDissolving = true;
	DissolutionBeginTime = GetWorld()->TimeSeconds;
	MeshComp->SetScalarParameterValueOnMaterials("EmissionStrength", 8.0f);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASExplosiveBarrel::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDissolving)
	{
		const float DissolveAmount = GetWorld()->TimeSeconds - DissolutionBeginTime;
		MeshComp->SetScalarParameterValueOnMaterials("DissolveAmount", DissolveAmount);
	}
}
