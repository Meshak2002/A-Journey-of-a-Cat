
#include "Wind.h"
#include "CatCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AWind::AWind() : windPower(20)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root= CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent= root;
	boxComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("box"));
	boxComponent->SetupAttachment(RootComponent);
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWind::BeginPlay()
{
	Super::BeginPlay();
	boxComponent->SetNotifyRigidBodyCollision(true);
	boxComponent->SetGenerateOverlapEvents(true);
	boxComponent->SetCollisionProfileName("OverlapAll");
	boxComponent->OnComponentBeginOverlap.AddDynamic(this,&AWind::OnBeginOverLap);
	boxComponent->OnComponentEndOverlap.AddDynamic(this,&AWind::OnEndOverLap);
}

// Called every frame
void AWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWind::OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACatCharacter* cat = Cast<ACatCharacter>(OtherActor);
	if(cat)
	{
		cat->windEffect = true;
		cat->windDirection = GetActorForwardVector();
		cat->windForce = windPower;
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Overlapping");
	}
}

void AWind::OnEndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ACatCharacter* cat = Cast<ACatCharacter>(OtherActor);
	if(cat)
	{
		cat->windEffect = false;
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Endlap");
		cat->windForce=0;
	}
}

