// Fill out your copyright notice in the Description page of Project Settings.

#include "CatCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ACatCharacter::ACatCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bubble = CreateDefaultSubobject<UStaticMeshComponent>("Bubble");
	bubble->SetupAttachment(RootComponent);
	burstEffect = CreateDefaultSubobject<UChildActorComponent>("BurstEffect");
	burstEffect->SetupAttachment(RootComponent);
}


bool ACatCharacter::isOnGround()
{
	FHitResult OutHit;
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 100); // Trace 50 units downward

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);

	if (bHit)
	{
		//	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,FString::Printf(TEXT("onGrnd :  %f"),catBreathe));
		return true;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Flying");
	return false;
}

void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();
	spawnPoint = GetActorLocation();
}

void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!animInstance || !springArmm) return;
	animInstance->isFlying = bCanFly;

	
	if (catBreathe < breatheRange && bCanFly)  //FLY & Bubble blow
	{
		springArmm->TargetArmLength = FMath::Lerp(springArmm->TargetArmLength , flyTargetArmLength, 1.5f*DeltaTime);
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		catBreathe += DeltaTime;
		staminaWidget->SetProgressValue(1-catBreathe/3);
		currentScale = bubble->GetRelativeScale3D();
		currentScale = FMath::Lerp(currentScale, finalScale, 0.5f*DeltaTime);
		bubble->SetRelativeScale3D(currentScale);
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "TICKFlying");

		float Time = GetWorld()->GetTimeSeconds();
		float SineOffset = FMath::Sin(Time * SineFrequency) * SineAmplitude;
		if(bubble->GetRelativeScale3D().X>0.1f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "TICKFlying");
			FVector addPos = GetActorLocation() + FVector(0, SineOffset*DeltaTime, 350*DeltaTime);
			SetActorLocation(addPos);
		}
		if(windEffect)
		{
			FVector addBreze = GetActorLocation() + windDirection * windForce;
			SetActorLocation(addBreze);
		}
		return;
	}
	else if(!bCanFly || catBreathe >= breatheRange)	//Bubble Shrink
	{
		FVector B(0, 0, 0);
		currentScale = bubble->GetRelativeScale3D();
		currentScale = FMath::Lerp(currentScale, B, 8.0f*DeltaTime);
		bubble->SetRelativeScale3D(currentScale);
		if(!isOnGround())			 //falling
			GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		else    //Reset to Walk
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			springArmm->TargetArmLength = FMath::Lerp(springArmm->TargetArmLength , walkTargetArmLength, 1.5f*DeltaTime);
			if(catBreathe>0)
			{
				catBreathe -= DeltaTime;
				staminaWidget->SetProgressValue(1-catBreathe/3);
			}
		}
	}
	
}



void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACatCharacter::Respawn()
{
	if(skeletalMesh)
		skeletalMesh->SetVisibility(false);
	GetWorld()->GetTimerManager().SetTimer(
	   TimerHandle,             // The handle for the timer
	   this,                    // The object on which the function is called
	   &ACatCharacter::TimerFunction, // The function to call
	   2.0f,                    // Time interval in seconds
	   false                     // Should the timer loop
   );
}

void ACatCharacter::TimerFunction()
{
	if(skeletalMesh)
		skeletalMesh->SetVisibility(true);
	SetActorLocation(spawnPoint);
}

void ACatCharacter::TimerFunction2()
{
	burstEffect->SetVisibility(false);
}

void ACatCharacter::BurstBubble()
{
	catBreathe = breatheRange;
	staminaWidget->SetProgressValue(1);
	currentScale = FVector(0, 0, 0);
	bubble->SetRelativeScale3D(currentScale);
	burstEffect->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(
	   TimerHandle,             // The handle for the timer
	   this,                    // The object on which the function is called
	   &ACatCharacter::TimerFunction2, // The function to call
	   .0001f,                    // Time interval in seconds
	   false                     // Should the timer loop
   );
}
