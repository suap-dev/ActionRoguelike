// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
	// Set this actor to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	LidOpenPitch = 110;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	                                 TEXT("Chest interacted with."));

	LidMesh->SetRelativeRotation(FRotator(LidOpenPitch, 0, 0));
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASItemChest::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
