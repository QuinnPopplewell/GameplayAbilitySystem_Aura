


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include <AbilitySystem/Abilities/AuraGameplayAbility.h>


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//Subscribe ClientEffectApplied to OnGameplayeffectAppliedDelegateToSelf
	//Any time a gameplay is applied, broadcast the target's tags
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);

	//Set the GameplayTags stored on the Component
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities)
{
	/*
	*	This function applies all GameplayAbilities stored in StartupAbilities
	*/

	//Loop through all ability classes on the StartupAbilities array
	for (class TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		//Create a GameplayAbilitySpec using the AbilityClass and its Level
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		//Check if the ability in the AbilitySpec is of type UAuraGameplayAbility
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			//Apply the ability's startup tags to the ability spec's DynamicAbilityTags so it can be referenced later
			//Give the ability to the owner's AbilitySystemComponent
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	// Return if the InputTag isn't valid
	if (!InputTag.IsValid()) return;
	
	// Get all of the ability specs stored on the ASC and loop through them
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//Check if the current spec has the passed in tag
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// Marks the ability spec as having receiving input
			AbilitySpecInputPressed(AbilitySpec);

			//Attempt to activate the ability spec now that it has received input
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	//Same as InputTagHeld but for being released
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//Create a tag container, put all asset tags in it, then broadcast it.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
