// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SBlinkProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASBlinkProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASBlinkProjectile();
	
protected:
 	UPROPERTY(EditDefaultsOnly)
 	UParticleSystemComponent* ExplosionEffectComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ExplosionDelay = 0.4f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TeleportDelay = 0.15f;

	FTimerHandle TimerHandle_Explosion;

	FTimerHandle TimerHandle_Teleport;

 	void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	void Explode();

	void Teleport();
 
	UFUNCTION()
 	void OnHit(
 		UPrimitiveComponent* HitComponent,
 		AActor* OtherActor,
 		UPrimitiveComponent* OtherComp,
 		FVector NormalImpulse,
 		const FHitResult& Hit);

};

