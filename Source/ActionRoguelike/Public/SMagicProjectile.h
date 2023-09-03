// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
// 
// 	// This is going to be our collision component.
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	USphereComponent* SphereComp;
// 
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	UProjectileMovementComponent* MovementComp;
// 
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	UParticleSystemComponent* EffectComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// 	UFUNCTION()
// 	void OnHit(
// 		UPrimitiveComponent* HitComponent,
// 		AActor* OtherActor,
// 		UPrimitiveComponent* OtherComp,
// 		FVector NormalImpulse,
// 		const FHitResult& Hit);
};
