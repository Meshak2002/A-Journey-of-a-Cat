// Fill out your copyright notice in the Description page of Project Settings.


#include "CatCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ACatCharacter::ACatCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bubble = CreateDefaultSubobject<UStaticMeshComponent>("Bubble");
	bubble->SetupAttachment(RootComponent);
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
		GEngine->AddOnScreenDebugMessage(
		-1,
		1,
		FColor::Red,
		FString::Printf(TEXT("onGrnd :  %f"),catBreathe));
		return true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Flying");
	return false;
}

void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (catBreathe < breatheRange && bCanFly)  //FLY & Bubble blow
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		catBreathe += DeltaTime;
		currentScale = bubble->GetRelativeScale3D();
		currentScale = FMath::Lerp(currentScale, finalScale, 0.05f);
		bubble->SetRelativeScale3D(currentScale);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "TICKFlying");

		FVector addPos = GetActorLocation() + FVector(0, 0, 10);
		SetActorLocation(addPos);
		return;
	}
	else if(!bCanFly || catBreathe >= breatheRange)	//Bubble Shrink
	{
		FVector B(0, 0, 0);
		currentScale = bubble->GetRelativeScale3D();
		currentScale = FMath::Lerp(currentScale, B, 0.1f);
		bubble->SetRelativeScale3D(currentScale);
		if(!isOnGround())
			GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		else
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			if(catBreathe>0)	catBreathe -= DeltaTime;
		}
	}
	
}

void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

