// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,
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
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	// AActor*, InstigatorActor,
	// USAttributeComponent, OwningComp,
	// float, NewHealth,
	// float, Delta

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);
};
