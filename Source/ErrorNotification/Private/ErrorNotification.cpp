#include "ErrorNotification.h"

#define LOCTEXT_NAMESPACE "FErrorNotificationModule"

// class FErrorNotificationCommandList : public TCommands<FErrorNotificationCommandList>
// {
// public:
// 	FErrorNotificationCommandList()
// 		: TCommands<FErrorNotificationCommandList>(TEXT("ErrorNotificationCommandList"), LOCTEXT("ErrorNotificationCommandList", "Error Notification Command Test"), NAME_None, FErrorNotificationStyle::Get().GetStyleSetName())
// 	{}
//
// 	virtual void RegisterCommands() override
// 	{
// 		UI_COMMAND( FirstCommandInfo, "First Test", "This is the first test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
// 		UI_COMMAND( SecondCommandInfo, "Second Test", "This is the second test menu item. Shows a keybinding", EUserInterfaceActionType::ToggleButton, FInputChord( ) );
//
// 		UI_COMMAND( ThirdCommandInfo, "Third Test", "This is the thrid test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
// 		UI_COMMAND( FourthCommandInfo, "Fourth Test", "This is the fourth test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
// 	}
// 	
// public:
// 	TSharedPtr<FUICommandInfo> FirstCommandInfo;
// 	TSharedPtr<FUICommandInfo> SecondCommandInfo;
// 	TSharedPtr<FUICommandInfo> ThirdCommandInfo;
// 	TSharedPtr<FUICommandInfo> FourthCommandInfo;
// };
//
// class FMenus
// {
// public:
// 	static void FillMenu1Entries( FMenuBuilder& MenuBuilder )
// 	{
// 		MenuBuilder.BeginSection("Menu1Entries");
// 		{
// 			MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().FirstCommandInfo );
// 			MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().SecondCommandInfo );
// 			MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().ThirdCommandInfo );
// 			MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().FourthCommandInfo );
// 		}
// 		MenuBuilder.EndSection();
//
// 		MenuBuilder.BeginSection("Menu1Entries3");
// 		{
// 			MenuBuilder.AddSubMenu( LOCTEXT("SubMenu", "Sub Menu"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
// 			MenuBuilder.AddSubMenu( LOCTEXT("SubMenu2IsALittleLonger", "Sub Menu 2 is a little longer"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
// 		}
// 		MenuBuilder.EndSection();
// 	}
//
// 	static void FillSubMenuEntries( FMenuBuilder& MenuBuilder )
// 	{
// 		MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().FirstCommandInfo );
// 		MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().SecondCommandInfo );
// 		MenuBuilder.AddSubMenu( LOCTEXT("SubMenu", "Sub Menu"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
// 		MenuBuilder.AddSubMenu( LOCTEXT("SubMenu2IsALittleLonger", "Sub Menu 2 is a little longer"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
// 	}
// };
//
// namespace MyTestSuiteMenu
// {
// 	TSharedRef<FWorkspaceItem> MenuRoot = FWorkspaceItem::NewGroup(NSLOCTEXT("FErrorNotificationModule", "MenuRoot", "MenuRoot") );
// 	TSharedRef<FWorkspaceItem> SuiteTabs = MenuRoot->AddGroup( NSLOCTEXT("FErrorNotificationModule", "SuiteTabs", "Test Suite Tabs") );
// 	TSharedRef<FWorkspaceItem> NestedCategory = SuiteTabs->AddGroup( NSLOCTEXT("FErrorNotificationModule", "NestedCategory", "Nested") );
// 	TSharedRef<FWorkspaceItem> DeveloperCategory = MenuRoot->AddGroup( NSLOCTEXT("FErrorNotificationModule", "DeveloperCategory", "Developer") );
// }

#undef LOCTEXT_NAMESPACE