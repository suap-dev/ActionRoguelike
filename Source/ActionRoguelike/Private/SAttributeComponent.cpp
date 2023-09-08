// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Health is set to default value during declaration (in header)
}


bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
