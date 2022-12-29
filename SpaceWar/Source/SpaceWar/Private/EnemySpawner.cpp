// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "SpaceShip.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnInterval = 2.0f;
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn,this,&AEnemySpawner::SpanEnemy,SpawnInterval,true,0.0f);
	
}

FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance = 0;
	FVector Location;
	while (Distance< MinimumDistanceToPlayer)
	{
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);
		Distance = (Location - SpaceShip->GetActorLocation()).Size();
	}

	return Location;
}

void AEnemySpawner::SpanEnemy()
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<AEnemy>(Enemy,GetGenerateLocation(),FRotator::ZeroRotator,SpawnParameters);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

