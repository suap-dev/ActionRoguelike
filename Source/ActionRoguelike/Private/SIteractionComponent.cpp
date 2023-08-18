// Fill out your copyright notice in the Description page of Project Settings.


#include "SIteractionComponent.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USIteractionComponent::USIteractionComponent()
{
	// Set this component to be initialized when the game starts,
	// and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USIteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USIteractionComponent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USIteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner(); // Get the owner of a component.

	FVector EyesLocation;	// it's actually going to be CHARACTER's eyes, not camera
	FRotator EyesRotation;
	MyOwner->GetActorEyesViewPoint(EyesLocation, EyesRotation);
	// The way GetActorEyesViewPoint works is defined in APawn
	// so we can redefined it later in SCharacter, since it inherits from APawn.
	// 
	// But we'd rather have the start of the line trace at the camera, not eyes.

	FVector Start = EyesLocation;
	FVector End = EyesLocation + (EyesRotation.Vector() * 500);

	FHitResult Hit;
	bool bTraceHit =
		GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);
	// We can debug-trace this line like so:

	DrawDebugLine( 
		GetWorld(), Start, End,
		bTraceHit ? FColor::Green : FColor::Red,
		false, 2.0f, 0, 1.0f);

	AActor* HitActor = Hit.GetActor();
	// ATTENTION - pay attention that we actually check if
	// HitActor Implements USGameplayInterface, not ISGameplayInterface
	if (HitActor && HitActor->Implements<USGameplayInterface>())
	{
		// AND THEN we actually use the ISGAmeplayInterface
		ISGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
	}

}
