// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_PushSoftWidget.h"

#include "Subsystems/FrontEndUISubsystem.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
                                                                         APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
                                                                         UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushToSoftWidgetToStack was pased a null soft widget class"));

	if(UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
		Node->RegisterWithGameInstance(World);
		Node->CachedOwningWorld = World;
		Node->CachedOwningPC = OwningPlayerController;
		Node->CachedSoftWidgetClass = InSoftWidgetClass;
		Node->CachedWidgetStackTag = InWidgetStackTag;
		Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget; 
		return Node; 
	}

	return nullptr; 
}

void UAsyncAction_PushSoftWidget::Activate()
{
	Super::Activate();

	UFrontEndUISubsystem* FrontEndUISubsystem = UFrontEndUISubsystem::Get(CachedOwningWorld.Get());

	FrontEndUISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](EAsyncPushingWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushingWidgetState::OnCreatedBeforePush:

				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
				
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				
				break;
			case EAsyncPushingWidgetState::AfterPush:

				AfterPush.Broadcast(PushedWidget);

				if(bCachedFocusOnNewlyPushedWidget)
				{
					if(UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}
				
				SetReadyToDestroy();
				
				break;
				
			default:;
			}
		});
	
}
