// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StaminaWidget.h"
#include "CatCharacter.generated.h"

UCLASS()
class JOURNEY_API ACatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* bubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanFly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector finalScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float breatheRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float catBreathe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaminaWidget* staminaWidget;

	bool isOnGround();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector currentScale;
};
