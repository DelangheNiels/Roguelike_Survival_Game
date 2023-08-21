// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDrop.h"

#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ABaseDrop::ABaseDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	_staticMesh->SetupAttachment(RootComponent);
	_sphereCollider = CreateDefaultSubobject<USphereComponent>(FName("HitCollider"));
	_sphereCollider->SetupAttachment(_staticMesh);
	_spline = CreateDefaultSubobject<USplineComponent>(FName("Spline Component"));
	_spline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseDrop::BeginPlay()
{
	Super::BeginPlay();
	_sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseDrop::OnPickUp);

	SetupSpline();
}

void ABaseDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveAlongSpline(DeltaTime);
}

void ABaseDrop::MoveAlongSpline(float DeltaTime)
{
	_distanceAlongSpline += _movementSpeed * DeltaTime;

	FTransform transform = _spline->GetTransformAtDistanceAlongSpline(_distanceAlongSpline, ESplineCoordinateSpace::World);
	FVector pos = transform.GetLocation();
	FVector newPos = GetActorLocation() + pos;
	SetActorLocation(pos);
}

void ABaseDrop::SetupSpline()
{
	_spline->RemoveSplinePoint(1);

	_spline->SetRelativeLocation(GetActorLocation());

	FVector midPoint = FVector(150, 0, 0);
	_spline->AddSplinePointAtIndex(midPoint, 1, ESplineCoordinateSpace::Local);
	FVector endSplinePoint = FVector(300, 0, 0);
	_spline->AddSplinePointAtIndex(endSplinePoint,2,ESplineCoordinateSpace::Local);

	//Random rotation
	float yaw = FMath::FRandRange(-180.f, 180.f);
	FRotator randomRotation = FRotator(0, yaw, 0);
	_spline->AddLocalRotation(randomRotation);

	//Set final point to the ground
	auto bounds = _staticMesh->Bounds;
	FVector endPoint = _spline->GetLocationAtSplinePoint(2,ESplineCoordinateSpace::Local);
	endPoint.Z -= GetActorLocation().Z - (bounds.BoxExtent.Z); //otherwise object is half in the ground

	_spline->SetLocationAtSplinePoint(2, endPoint, ESplineCoordinateSpace::Local);

}


