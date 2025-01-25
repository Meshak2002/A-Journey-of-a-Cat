#include "CatPlayer.h"

ACatPlayer::ACatPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ACatPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ACatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

