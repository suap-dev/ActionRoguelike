// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "SAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


ASMagicProjectile::ASMagicProjectile()
{
	ExplosionEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionEffectComp");
	ExplosionEffectComp->SetupAttachment(RootComponent);
	ExplosionEffectComp->SetAutoActivate(false);
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}

// TODO: Figure out when and if I want to distinct between OnOverlap and OnHit
void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent,
                                       AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex,
                                       bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		// we cast because GetComponentByClass returns generic *UActorComponent
		if (USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(
			OtherActor->GetComponentByClass(USAttributeComponent::StaticClass())))
		{
			AttributeComp->ApplyHealthChange(-Damage);
		}

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffectComp->Template, GetActorTransform());
		Destroy();
	}
}
