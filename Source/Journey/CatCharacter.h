// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatAnimInstance.h"
#include "GameFramework/Character.h"
#include "StaminaWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "CatCharacter.generated.h"

UCLASS()
class JOURNEY_API ACatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* springArmm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* burstEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* skeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* bubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* montageJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCatAnimInstance* animInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanFly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector finalScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float breatheRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float catBreathe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SineAmplitude = 20.0f; // Adjust for larger wavy motion
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SineFrequency = 2.0f; // Increase for faster oscillation

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float walkTargetArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float flyTargetArmLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaminaWidget* staminaWidget;

	bool isOnGround();

	bool windEffect;
	float windForce;
	FVector windDirection;

	FVector spawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTimerHandle TimerHandle; 
	UFUNCTION(BlueprintCallable)
	void TimerFunction();

	UFUNCTION(BlueprintCallable)
	void TimerFunction2();

	UFUNCTION(BlueprintCallable)
	void BurstBubble();
	
	UFUNCTION(BlueprintCallable)
	void Respawn();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector currentScale;
};
