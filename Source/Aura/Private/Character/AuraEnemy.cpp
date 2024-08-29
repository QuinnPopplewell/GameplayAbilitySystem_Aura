

#include "Character/AuraEnemy.h"
#include "Components/CapsuleComponent.h"

AAuraEnemy::AAuraEnemy()
{
    bHighlighted = false;
}

void AAuraEnemy::HighlightActor()
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy Highlighted"));
    bHighlighted = true;
}

void AAuraEnemy::UnHighlightActor()
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy UnHighlighted"));
    bHighlighted = false;
}
