// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontEndUISubsystem.h"

#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"

UFrontEndUISubsystem* UFrontEndUISubsystem::Get(const UObject* WorldContextObject)
{
	if(GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UFrontEndUISubsystem>(World->GetGameInstance());
	}

	return nullptr; 
}

bool UFrontEndUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if(!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty(); 
	}
	
	return false;
}

void UFrontEndUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	
	CreatedPrimaryLayout = InCreatedWidget;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), FString("Primary layout widget stored"));

}

void UFrontEndUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushingWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget"));

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass, InWidgetStackTag, this, AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(LoadedWidgetClass && CreatedPrimaryLayout);

				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
				
				UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallback(EAsyncPushingWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					});
				AsyncPushStateCallback(EAsyncPushingWidgetState::AfterPush, CreatedWidget);
			}));
}

void UFrontEndUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFrontEndUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}
