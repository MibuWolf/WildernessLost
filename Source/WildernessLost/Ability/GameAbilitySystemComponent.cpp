// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystemComponent.h"

UGameAbilitySystemComponent::UGameAbilitySystemComponent()
{

}

void UGameAbilitySystemComponent::AutoGiveAbilites()
{
	for (const TPair<int32, TSubclassOf<UGameAbility>>& Pair : AllPossibleAbilities)
	{
		UGameAbility* pAbility = Cast<UGameAbility>(Pair.Value.GetDefaultObject());
		if (pAbility->CanAutoGive())
		{
			GiveAbility(FGameplayAbilitySpec(Pair.Value, 1, static_cast<int32>(pAbility->InputID), GetOwner()));
		}
	}
}

void UGameAbilitySystemComponent::TryAddAbility(int32 AbilityID)
{

}

void UGameAbilitySystemComponent::TryRemoveAbility(int32 AbilityID)
{
}

void UGameAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
	if (!AbilityComboCount.Contains(InputID))
		AbilityComboCount.Add(InputID, 0);

	FString ComboTag = FString::Printf(TEXT("Skill.Combo.%d"), InputID);
	FGameplayTagContainer tagContainer;
	tagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(*ComboTag)));
	bool bCombo = false;
	if (HasAnyMatchingGameplayTags(tagContainer))
	{
		AbilityComboCount[InputID] = AbilityComboCount[InputID] + 1;

		bCombo = true;
	}

	// Consume the input if this InputID is overloaded with GenericConfirm/Cancel and the GenericConfim/Cancel callback is bound
	if (IsGenericConfirmInputBound(InputID))
	{
		LocalInputConfirm();
		return;
	}

	if (IsGenericCancelInputBound(InputID))
	{
		LocalInputCancel();
		return;
	}

	// ---------------------------------------------------------
	int32 count = 0;
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.InputID == InputID)
		{
			if (count != AbilityComboCount[InputID])
			{
				count++;
				continue;
			}

			if (Spec.Ability)
			{
				Spec.InputPressed = true;
				if (Spec.IsActive())
				{
					if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
					{
						ServerSetInputPressed(Spec.Handle);
					}

					AbilitySpecInputPressed(Spec);

					// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
				}
				else
				{
					if (!bCombo && count != 0)
					{
						AbilityComboCount[InputID] = 0;
						AbilityLocalInputPressed(InputID);
						return;
					}
					// Ability is not active, so try to activate it
					TryActivateAbility(Spec.Handle);
				}

				return;
			}
		}
	}
}
