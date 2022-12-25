// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/PlayerController.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "TimerManager.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponet = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponet"));
	RootComponent = CollisionComponet;
	
	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(ShipSM);

	TimeBetweenShot = 0.6f;

	speed = 2500.0f;

}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;
	
}

void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y,GetActorLocation().Z);
	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	SetActorRotation(Rotator);
}

void ASpaceShip::MoveUp(float value)
{
	AddMovementInput(FVector::ForwardVector,value);
}

void ASpaceShip::MoveRight(float value)
{
	AddMovementInput(FVector::RightVector,value);
}

void ASpaceShip::Move()
{
	AddActorWorldOffset(ConsumeMovementInputVector()*speed*FApp::GetDeltaTime(), true);
}

void ASpaceShip::Fire()
{
	if (Bullet)
	{
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParameters);
	}
}

void ASpaceShip::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShots, this, &ASpaceShip::Fire, TimeBetweenShot,true,0.0f);
}

void ASpaceShip::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShots);
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAtCursor();
	Move();
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASpaceShip::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShip::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::EndFire);


}

