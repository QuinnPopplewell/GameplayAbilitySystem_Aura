

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM()
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM()
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	bool bDestroyOnEffectRemoval = false;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
	float ActorLevel = 1.f;
};
