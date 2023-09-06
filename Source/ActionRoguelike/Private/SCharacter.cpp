// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "../Private/KismetTraceUtils.h"
#include "SAttributeComponent.h"


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

	AtrributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

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
		BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);


	PlayerInputComponent->
		BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);

	PlayerInputComponent->
		BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);

	PlayerInputComponent->
		BindAction("TertiaryAttack", IE_Pressed, this, &ASCharacter::TertiaryAttack);

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


void ASCharacter::PrimaryInteract()
{
	// We don't have to check for nullptr, because we exactly know 
	// what is the lifetime of the owner of this particular call.
	InteractionComp->PrimaryInteract();

}



void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimiaryAttackAnimation);

	GetWorldTimerManager().SetTimer(
		TimerHandle_PrimaryAttack, this,
		&ASCharacter::PrimaryAttack_TimeElapsed, PrimaryAttackFireDelay);
}


void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector MuzzleLocation = GetMesh()->GetSocketLocation(PrimaryAttackMuzzleName);
	FRotator AimRotation = GetAimRotationFromMuzzle(MuzzleLocation);

	DrawDebugLine(
		GetWorld(), MuzzleLocation, MuzzleLocation + AimRotation.Vector() * 5000,
		FColor::Purple, false, 2.0f);

	// TODO: READ ON COLLISIONS: https://docs.unrealengine.com/5.2/en-US/collision-in-unreal-engine/

	FTransform SpawnTransform = FTransform(AimRotation, MuzzleLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, SpawnTransform, SpawnParams);

}



// TODO: SecondaryAttack is ALMOST IDENTICAL to PrimaryAttack. DRY!
// TODO: Should all attacks share the TimerHandle?
void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(SecondaryAttackAnimation);

	GetWorldTimerManager().SetTimer(
		TimerHandle_SecondaryAttack, this,
		&ASCharacter::SecondaryAttack_TimeElapsed, SecondaryAttackFireDelay);
}


void ASCharacter::SecondaryAttack_TimeElapsed()
{
	FVector MuzzleLocation = GetMesh()->GetSocketLocation(SecondaryAttackMuzzleName);
	FRotator AimRotation = GetAimRotationFromMuzzle(MuzzleLocation);

	DrawDebugLine(
		GetWorld(), MuzzleLocation, MuzzleLocation + AimRotation.Vector() * 5000,
		FColor::Purple, false, 2.0f);

	// TODO: READ ON COLLISIONS: https://docs.unrealengine.com/5.2/en-US/collision-in-unreal-engine/

	FTransform SpawnTransform = FTransform(AimRotation, MuzzleLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, SpawnTransform, SpawnParams);

}


void ASCharacter::TertiaryAttack()
{
	PlayAnimMontage(TertiaryAttackAnimation);

	GetWorldTimerManager().SetTimer(
		TimerHandle_TertiaryAttack, this,
		&ASCharacter::TertiaryAttack_TimeElapsed, TertiaryAttackFireDelay);
}


void ASCharacter::TertiaryAttack_TimeElapsed()
{
	FVector MuzzleLocation = GetMesh()->GetSocketLocation(TertiaryAttackMuzzleName);
	FRotator AimRotation = GetAimRotationFromMuzzle(MuzzleLocation);

	DrawDebugLine(
		GetWorld(), MuzzleLocation, MuzzleLocation + AimRotation.Vector() * 5000,
		FColor::Purple, false, 2.0f);

	// TODO: READ ON COLLISIONS: https://docs.unrealengine.com/5.2/en-US/collision-in-unreal-engine/

	FTransform SpawnTransform = FTransform(AimRotation, MuzzleLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(TertiaryProjectileClass, SpawnTransform, SpawnParams);

}

FRotator ASCharacter::GetAimRotationFromMuzzle(const FVector& MuzzleLocation, float Range /*= 5000.0f*/)
{
	FVector TraceStart = CameraComp->GetComponentLocation();
	FVector TraceEnd = TraceStart + CameraComp->GetForwardVector() * Range;

	FHitResult HitResult;
	bool bHit =
		GetWorld()->LineTraceSingleByProfile(HitResult, TraceStart, TraceEnd, "Projectile");

	DrawDebugLineTraceSingle(
		GetWorld(), TraceStart, TraceEnd, EDrawDebugTrace::ForDuration,
		bHit, HitResult,
		FLinearColor::Blue, FLinearColor::Green, 2.0f);

	// 	FRotator AimRotation;
	// 	if (bHit)
	// 	{
	// 		AimRotation = (HitResult.Location - MuzzleLocation).Rotation();
	// 
	// 	}
	// 	else
	// 	{
	// 		AimRotation = (End - MuzzleLocation).Rotation();
	// 
	// 	}
	// 
	// 	return AimRotation;

	return ((bHit ? HitResult.Location : TraceEnd) - MuzzleLocation).Rotation();
}
