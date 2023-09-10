// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "SCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts,
	// and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USInteractionComponent::PrimaryInteract() const
{
	FVector Start;
	FVector End;
	AActor* MyOwner = GetOwner(); // Get the owner of a component.

	if (const ASCharacter* CharacterOwner = Cast<ASCharacter>(MyOwner))
	{
		const UCameraComponent* Camera = CharacterOwner->GetComponentByClass<UCameraComponent>();

		Start = Camera->GetComponentLocation();
		End = Start + Camera->GetComponentRotation().Vector() * 700;
	}
	else
	{
		FVector EyesLocation; // it's actually going to be Actor's eyes, not camera
		FRotator EyesRotation;
		MyOwner->GetActorEyesViewPoint(EyesLocation, EyesRotation);
		// The way GetActorEyesViewPoint works is defined in APawn
		// so we can redefined it later in SCharacter, since it inherits from APawn.
		// 
		// But we'd rather have the start of the line trace at the camera, not eyes.

		Start = EyesLocation;
		End = Start + EyesRotation.Vector() * 500;
	}

	// we're using the SweepMulti instead of LineTrace for now
	// the code below is left only for learning purpose
	// 
	// 	FHitResult Hit;
	// 
	// 	FCollisionObjectQueryParams ObjectQueryParams;
	// 	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	// 
	// 	bool bTraceHit =
	// 		GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);
	// 	AActor* HitActor = Hit.GetActor();
	// 
	// 	// ATTENTION - pay attention that we actually check if
	// 	// HitActor Implements USGameplayInterface, not ISGameplayInterface
	// 	if (HitActor && HitActor->Implements<USGameplayInterface>())
	// 	{
	// 		// AND THEN we actually use the ISGameplayInterface
	// 		ISGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
	// 	}
	// 	// We can draw a debug line along the trace, like so:
	// 	DrawDebugLine(
	// 		GetWorld(), Start, End,
	// 		bTraceHit ? FColor::Green : FColor::Red,
	// 		false, 2.0f, 0, 1.5f);


	TArray<FHitResult> OutHits;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionShape;
	constexpr float Collision_Sphere_Radius = 35.0f;
	CollisionShape.SetSphere(Collision_Sphere_Radius);

	GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape);

	// DebugLine representing the path of the Sweep.
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 1.5f);


	for (FHitResult& OutHit : OutHits)
	{
		// DebugSphere that representing the OutHit that hit something
		DrawDebugSphere(GetWorld(), OutHit.Location, Collision_Sphere_Radius,
		                static_cast<int32>(Collision_Sphere_Radius / 2), FColor::Green,
		                false, 2.0f, 0, 0.75f);

		if (AActor* HitActor = OutHit.GetActor(); HitActor && HitActor->Implements<USGameplayInterface>())
		{
			ISGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
			break; // without this break we'd open everything in the path of the sweep
		}
	}
}
