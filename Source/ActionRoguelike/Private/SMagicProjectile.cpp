// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent,
                                       AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex,
                                       bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString(__FUNCTION__));

	if (OtherActor && OtherActor != GetInstigator())
	{
		// We cast because GetComponentByClass returns generic *UActorComponent
		if (USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(
			OtherActor->GetComponentByClass(USAttributeComponent::StaticClass())))
		{
			UE_LOG(LogTemp, Log, TEXT("Done %.1f damage"), Damage);

			AttributeComp->ApplyHealthChange(-Damage);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No attribute component, no damage done."));
	}
}
