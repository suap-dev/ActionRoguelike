// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	// Trigger when health is changed (damage/healing)
	AttributeComp->HealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
                                    const float Delta)
{
	// We don't check for null, because we created it in the constructor. It's not a function parameter.
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->TimeSeconds);
	}
}
