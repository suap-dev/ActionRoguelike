// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHealthChanged,
                                              AActor*, InstigatorActor,
                                              USAttributeComponent*, OwningComp,
                                              float, NewHealth,
                                              float, Delta);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health = 100;

	// HealthMax, Stamina, Strength

public:
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	// TODO: Recall how this actually works (also -- look at the top of this file).
	// As I understand it atm -- AttributeComponent broadcasts the fact that Health Changed,
	// an other classes can subscribe to listen for this event.	
	UPROPERTY(BlueprintAssignable)
	FHealthChanged HealthChanged;
	// AActor*, InstigatorActor,
	// USAttributeComponent, OwningComp,
	// float, NewHealth,
	// float, Delta

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);
};
