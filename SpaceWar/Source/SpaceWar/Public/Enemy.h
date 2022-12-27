// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class USphereComponent;
class ASpaceShip;

UCLASS()
class SPACEWAR_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Component")
	UStaticMeshComponent* ShipSM;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveTowardsPlayer(float DealtaTime);
	ASpaceShip* SpaceShip;
	float Speed = 300.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
