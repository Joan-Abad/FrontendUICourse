// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find the widget stack by the tag %s"), *InTag.ToString());
	
	return RegisteredWidgetStackMap.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	//Design means if we are in the designer, aka editor not runtime. 
	if(!IsDesignTime())
	{
		if(!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), FString("Widget stack registered: ") + InStackTag.ToString());
		}
	}
}
