// Fill out your copyright notice in the Description page of Project Settings.


#include "FrontendGameplayTags.h"



namespace FrontendGameplayTags
{
	//Frontend widget stack
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Modal, "Frontend.WidgetStack.Modal")
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameMenu, "Frontend.WidgetStack.GameMenu")
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameHud, "Frontend.WidgetStack.GameHud")
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_FrontEnd, "Frontend.WidgetStack.FrontEnd")

	//Frontend widgets
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_PressAnyScreen, "Frontend.Widget.PressAnyScreen")
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_MainMenuScreen, "Frontend.Widget.MainMenuScreen")	
}