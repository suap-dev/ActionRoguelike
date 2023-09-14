// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}

// TODO: Why is OnHit not triggering when OnOverlap is. ? :|
// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void ASMagicProjectile::OnActorOverlap([[maybe_unused]] UPrimitiveComponent* OverlappedComponent,
                                       AActor* OtherActor,
                                       [[maybe_unused]] UPrimitiveComponent* OtherComp,
                                       [[maybe_unused]] int32 OtherBodyIndex,
                                       [[maybe_unused]] bool bFromSweep,
                                       [[maybe_unused]] const FHitResult& SweepResult)
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
