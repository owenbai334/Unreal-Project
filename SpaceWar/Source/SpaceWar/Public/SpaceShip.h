// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class ABullet;
class USoundCue;

UCLASS()
class SPACEWAR_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
		
	UPROPERTY(VisibleAnywhere, Category="Component")
	USphereComponent* CollisionComponet;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Move")
	float speed;

	FTimerHandle TimerHandle_BetweenShots;
	FTimerHandle TimerHandle_Restart;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float TimeBetweenShot;

	APlayerController* PC;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<ABullet> Bullet;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* GameOverCue;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;

	bool bDead;

	virtual void BeginPlay() override;
	
	void LookAtCursor();
	
	void MoveUp(float value);
	void MoveRight(float value);
	void Move();

	void Fire();
	void StartFire();
	void EndFire();

	void RestartLevil();
	void OnDeath();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FORCEINLINE bool GetBDead()
	{
		return bDead;
	}

};
