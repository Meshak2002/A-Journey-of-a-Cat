// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "StaminaWidget.generated.h"

/**
 * 
 */
UCLASS()
	class JOURNEY_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetProgressValue(float value);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess=true	))
	UProgressBar* progressBar=nullptr;
};
