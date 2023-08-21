// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObjective.h"

#include "Components/SphereComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"

#include "../UI/ObjectiveProgressBar.h"
#include "../UI/ObjectivePointer.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/HealthComponent.h"

#include "Blueprint/UserWidget.h"


// Sets default values
ABaseObjective::ABaseObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_defaultRootComponent = CreateDefaultSubobject<USceneComponent>(FName("DefaultRootComponent"));
	SetRootComponent(_defaultRootComponent);

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	_staticMesh->SetupAttachment(GetRootComponent());

	_collisionSphere = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));
	_collisionSphere->SetupAttachment(_staticMesh);

	_progressWidget = CreateDefaultSubobject<UWidgetComponent>(FName("ObjectiveProgress Widget"));
	_progressWidget->SetupAttachment(_staticMesh);
}

// Called when the game starts or when spawned
void ABaseObjective::BeginPlay()
{
	Super::BeginPlay();

	//Collision
	if (!_collisionSphere)
		return;
	_collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseObjective::OverlapBegin);
	_collisionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseObjective::OnEndOverlap);

	//// Pointer widget
	if (!_pointerWidgetClass || !_objectivePointerImage)
		return;
	_pointerWidget = Cast<UObjectivePointer>(CreateWidget(GetWorld(), _pointerWidgetClass));
	if (!_pointerWidget)
		return;
	_pointerWidget->SetImage(_objectivePointerImage);
	_pointerWidget->SetObjectivePosition(GetActorLocation());
	_pointerWidget->AddToViewport();

	//Progress widget
	_objectiveProgress = Cast<UObjectiveProgressBar>(_progressWidget->GetUserWidgetObject());
	if (!_objectiveProgress)
		return;
	_objectiveProgress->OnCompleted.AddUObject(this, &ABaseObjective::OnObjectiveCompleted);
	
}

// Called every frame
void ABaseObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_despawnTimer += DeltaTime;
	if (_despawnTimer >= _despawnTime)
		DestroyObjective();


	if (!_isPlayerInRange)
		return;

	_currentProgressTime += DeltaTime;
	_objectiveProgress->SetFillPercentage(GetFillPercentage());
}


float ABaseObjective::GetFillPercentage()
{
	return _currentProgressTime / _timeToFillProgress;
}

void ABaseObjective::OnObjectiveCompleted()
{
	_despawnTimer = 0.0f;
	OnObjectiveDestroyed.Broadcast(this);
	_objectiveProgress->OnCompleted.RemoveAll(this);
	_pointerWidget->RemoveFromParent();
}

void ABaseObjective::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerCharacter>(OtherActor);

	if (!player)
		return;

	_isPlayerInRange = true;
	_despawnTimer = 0.0f;

}

void ABaseObjective::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto player = Cast<APlayerCharacter>(OtherActor);

	if (!player)
		return;

	_isPlayerInRange = false;

}

void ABaseObjective::DestroyObjective()
{
	_despawnTimer = 0.0f;
	OnObjectiveDestroyed.Broadcast(this);
	_objectiveProgress->OnCompleted.RemoveAll(this);
	_pointerWidget->RemoveFromParent();
	this->Destroy();
}

