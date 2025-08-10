// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "FrontEndUISubsystem.generated.h"

class UWidget_ActivatableBase;
class UWidget_PrimaryLayout;
struct FGameplayTag;

enum class EAsyncPushingWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

/**
 * 
 */
UCLASS()
class UI_UDEMY_API UFrontEndUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public: 
	static UFrontEndUISubsystem* Get(const UObject* WorldContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushingWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;  
};
