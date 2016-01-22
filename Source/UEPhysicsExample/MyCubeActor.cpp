// Fill out your copyright notice in the Description page of Project Settings.

#include "UEPhysicsExample.h"
#include "MyStaticMeshComponent.h"
#include "MyCubeActor.h"

#define LOCTEXT_NAMESPACE "MyCubeActor"


AMyCubeActor::AMyCubeActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Init parameters
	StartVelocity = 1000.0f;
	KSpring = 100.0f;
	Damping = 0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube'"));

	USceneComponent *root = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	SetRootComponent(root);

	Cube = PCIP.CreateDefaultSubobject <UMyStaticMeshComponent>(this, TEXT("Cube"));
	Cube->SetStaticMesh(CubeMesh.Object);
	Cube->AttachTo(root);

	DebugPanel = PCIP.CreateDefaultSubobject <UTextRenderComponent>(this, TEXT("Debug panel"));
	DebugPanel->SetRelativeLocation(FVector(0, -100, 0));
	DebugPanel->AttachTo(root);
	DebugPanel->SetXScale(2);
	DebugPanel->SetYScale(2);
	DebugPanel->SetText(FText::FromString(TEXT("")));
	DebugPanel->SetTextRenderColor(FColor(0, 0, 0));
}

void AMyCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMotionAnalysis(DeltaTime);
}

void AMyCubeActor::UpdateMotionAnalysis(float DeltaTime)
{
	static int32 lastDir = 0, lastH = 0;
	static double lastPeriodStart = 0, currPeriod = 0, currAmplitude = 0;

	float currH = Cube->GetComponentLocation().Z - Cube->StartH;
	int currDir = currH > lastH ? 1 : -1;

	int32 Seconds;
	float PartialSeconds;
	UGameplayStatics::GetAccurateRealTime(GetWorld(), Seconds, PartialSeconds);
	double Time = (double)Seconds + PartialSeconds;

	if (lastPeriodStart == 0) lastPeriodStart = Time;
	else {
		if (lastDir != currDir) {
			currPeriod = (Time - lastPeriodStart) * 2;
			currAmplitude = FMath::Abs(currH) * 2;

			lastPeriodStart = Time;
		}
	}

	int32 fps = FMath::RoundToInt(1 / DeltaTime);
	DebugPanel->SetText(FText::Format(LOCTEXT("Debug Panel", "{0} FPS\n{1} sec\n{2} Amplitude"), FText::AsNumber(fps), FText::AsNumber(currPeriod), FText::AsNumber(currAmplitude)));

	lastDir = currDir;
	lastH = currH;
}

#undef LOCTEXT_NAMESPACE