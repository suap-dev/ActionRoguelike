// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

public:
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
	           AActor* OtherActor,
	           UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);

	// UFUNCTION()
	// void BeginOverlap(
	// 	UPrimitiveComponent* OverlappedComponent,
	// 	AActor* OtherActor,
	// 	UPrimitiveComponent* OtherComp,
	// 	int32 OtherBodyIndex,
	// 	bool bFromSweep,
	// 	const FHitResult& SweepResult);

	UFUNCTION()
	void Explode() const;

	UFUNCTION()
	void Destroy();

	UFUNCTION()
	void StartDissolving();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_Explosion;

	FTimerHandle TimerHandle_Destruction;

	bool bIsDissolving;
	float DissolutionBeginTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
};
