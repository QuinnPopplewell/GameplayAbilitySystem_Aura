

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	
	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// End of Enemy Interface

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
};
