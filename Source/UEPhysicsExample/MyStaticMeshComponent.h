#pragma once

#include "Components/StaticMeshComponent.h"
#include "MyStaticMeshComponent.generated.h"

USTRUCT()
struct FMySecondaryTickFunction : public FTickFunction
{
	GENERATED_USTRUCT_BODY()

	class UMyStaticMeshComponent* Target;

	UEPHYSICSEXAMPLE_API virtual void ExecuteTick(
		float DeltaTime,
		ELevelTick TickType,
		ENamedThreads::Type CurrentThread,
		const FGraphEventRef& MyCompletionGraphEvent) override;

	UEPHYSICSEXAMPLE_API virtual FString DiagnosticMessage() override;
};

template<>
struct TStructOpsTypeTraits<FMySecondaryTickFunction> : public TStructOpsTypeTraitsBase
{
	enum
	{
		WithCopy = false
	};
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEPHYSICSEXAMPLE_API UMyStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UMyStaticMeshComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TickPostPhysics(float DeltaSeconds, ELevelTick TickType, FMySecondaryTickFunction& ThisTickFunction);

	float StartH;

	UPROPERTY(EditDefaultsOnly, Category = "Tick")
		FMySecondaryTickFunction SecondaryComponentTick;

private:
	FCalculateCustomPhysics OnCalculateCustomPhysics;

	void SubstepTick(float DeltaTime, FBodyInstance* BodyInstance);
	void DoPhysics(float DeltaTime, bool InSubstep);

	class AMyCubeActor *owner;
	int32 FrameCount;

	physx::PxRigidBody* PRigidBody;

	FORCEINLINE FVector  GetCurrentLocation();
	FORCEINLINE FRotator GetCurrentRotation();
	FORCEINLINE FVector  GetCurrentVelocity();
	FORCEINLINE FVector  GetCurrentAngularVelocity();
};
