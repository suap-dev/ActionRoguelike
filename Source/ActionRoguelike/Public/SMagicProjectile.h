// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

// class UParticleSystemComponent;

/**
 *
 */

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASMagicProjectile();

protected:
	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* ExplosionEffectComp;

	void PostInitializeComponents() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = 20.0f;

	UFUNCTION(BlueprintCallable)
	void OnActorOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
