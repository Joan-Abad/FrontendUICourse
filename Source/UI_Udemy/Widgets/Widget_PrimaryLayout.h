// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UI_UDEMY_API UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public: 
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag) const; 
	
protected:
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);
	
private:
	
	//Transient means that this variable will only be filled with values at runtime, so at first load it will be empty, no previously loaded saved values. 
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap; 
};
