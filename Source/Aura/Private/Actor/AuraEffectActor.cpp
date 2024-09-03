#include "Actor/AuraEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{	
	/*
		In short
		Get the Target's Ability system component
		Turn it into a context handle
		Make an effect spec handle from the ASC
		Apply that effect

		Optionally, a source object can be set for the effect context
	*/

	// Get the target's Ability System Component, then return if it doesn't exist
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	// Crash if GameplayEffectClass missing
	check(GameplayEffectClass)

	// Log the Target's ability system component as the EffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();

	//Set this actor as the source object for the EffectContextHandle
	EffectContextHandle.AddSourceObject(this);

	// Create an EffectSpecHandle calling MakeOutgoingSpec from the TargetASC
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	// Given the GameplayClass, Level, and EffectContextHandle, apply the GameplayEffectSpec, dereferenceing the EffectSpecHandle
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
