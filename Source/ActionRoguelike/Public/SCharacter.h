// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// TODO: fix the U_PROPERTIES
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USAttributeComponent* AttributeComp;

protected:
	UPROPERTY(EditAnywhere, Category = "Attack - Primary", DisplayName = "Projectile Class")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack - Primary", DisplayName = "Attack Animation")
	UAnimMontage* PrimaryAttackAnimation;

	UPROPERTY(EditAnywhere, Category = "Attack - Primary", DisplayName = "Fire Delay")
	float PrimaryAttackFireDelay;

	UPROPERTY(EditAnywhere, Category = "Attack - Primary", DisplayName = "Muzzle Socket")
	FName PrimaryAttackMuzzleName;

	FTimerHandle TimerHandle_PrimaryAttack;


	UPROPERTY(EditAnywhere, Category = "Attack - Secondary", DisplayName = "Projectile Class")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack - Secondary", DisplayName = "Attack Animation")
	UAnimMontage* SecondaryAttackAnimation;

	UPROPERTY(EditAnywhere, Category = "Attack - Secondary", DisplayName = "Fire Delay")
	float SecondaryAttackFireDelay;

	UPROPERTY(EditAnywhere, Category = "Attack - Secondary", DisplayName = "Muzzle Socket")
	FName SecondaryAttackMuzzleName;

	FTimerHandle TimerHandle_SecondaryAttack;


	UPROPERTY(EditAnywhere, Category = "Attack - Tertiary", DisplayName = "Projectile Class")
	TSubclassOf<AActor> TertiaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack - Tertiary", DisplayName = "Attack Animation")
	UAnimMontage* TertiaryAttackAnimation;

	UPROPERTY(EditAnywhere, Category = "Attack - Tertiary", DisplayName = "Fire Delay")
	float TertiaryAttackFireDelay;

	UPROPERTY(EditAnywhere, Category = "Attack - Tertiary", DisplayName = "Muzzle Socket")
	FName TertiaryAttackMuzzleName;

	FTimerHandle TimerHandle_TertiaryAttack;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MoveForward(float Value);

	void MoveRight(float Value);


	void PrimaryInteract();


	void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();


	void SecondaryAttack();

	void SecondaryAttack_TimeElapsed();


	void TertiaryAttack();

	void TertiaryAttack_TimeElapsed();


	FRotator GetAimRotationFromMuzzle(const FVector& MuzzleLocation, float Range = 5000.0f) const;
};
