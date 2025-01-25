// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaWidget.h"


void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(progressBar)
		SetProgressValue(1);
}

void UStaminaWidget::SetProgressValue(float value)
{
	progressBar->SetPercent(value);
}