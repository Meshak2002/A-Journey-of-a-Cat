// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Wind.generated.h"

class UBoxComponent;

UCLASS()
class JOURNEY_API AWind : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWind();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* root;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* boxComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UArrowComponent* arrow;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float windPower;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
