// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "../Private/KismetTraceUtils.h"


// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

}


// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->
		BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);

	PlayerInputComponent->
		BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

}


void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);

}


void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	/*
	 * X = Forward
	 * Y = Right
	 * Z = Up
	 *
	 **/

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	//FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRot);

	AddMovementInput(RightVector, Value);

}


void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(
		TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.15f);

	// 	GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}


void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	// TODO: Get direction from what is camera directly looking at
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetForwardVector() * 5000;

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByProfile(HitResult, Start, End, "Projectile");

	DrawDebugLineTraceSingle(
		GetWorld(), Start, End, EDrawDebugTrace::ForDuration,
		bHit, HitResult,
		FLinearColor::Blue, FLinearColor::Green, 2.0f);

	FRotator AimRotation;
	if (bHit)
	{
		AimRotation = (HitResult.Location - RightHandLocation).Rotation();

	}
	else
	{
		AimRotation = CameraComp->GetComponentRotation();

	}

	DrawDebugLine(
		GetWorld(), RightHandLocation, RightHandLocation + AimRotation.Vector() * 2000,
		FColor::Purple, false, 2.0f);

	// TODO: READ ON COLLISIONS: https://docs.unrealengine.com/5.2/en-US/collision-in-unreal-engine/

	FTransform SpawnTransform = FTransform(AimRotation, RightHandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);

}

void ASCharacter::PrimaryInteract()
{
	// We don't have to check for nullptr, because we exactly know 
	// what is the lifetime of the owner of this particular call.
	InteractionComp->PrimaryInteract();
}

