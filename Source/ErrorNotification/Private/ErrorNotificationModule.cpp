// Copyright Epic Games, Inc. All Rights Reserved.

#include "ErrorNotificationModule.h"
#include "ErrorNotificationStyle.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "WorkspaceMenuStructureModule.h"
#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "Interfaces/IPluginManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Testing/STestSuite.h"

#define LOCTEXT_NAMESPACE "FErrorNotificationModule"

FLogCategoryLogErrorNoti LogErrorNoti;

namespace MyTestSuiteMenu
{
	TSharedRef<FWorkspaceItem> MenuRoot = FWorkspaceItem::NewGroup(NSLOCTEXT("FErrorNotificationModule", "MenuRoot", "MenuRoot") );
	TSharedRef<FWorkspaceItem> SuiteTabs = MenuRoot->AddGroup( NSLOCTEXT("FErrorNotificationModule", "SuiteTabs", "Test Suite Tabs") );
	TSharedRef<FWorkspaceItem> NestedCategory = SuiteTabs->AddGroup( NSLOCTEXT("FErrorNotificationModule", "NestedCategory", "Nested") );
	TSharedRef<FWorkspaceItem> DeveloperCategory = MenuRoot->AddGroup( NSLOCTEXT("FErrorNotificationModule", "DeveloperCategory", "Developer") );
}


class FErrorNotificationCommandList : public TCommands<FErrorNotificationCommandList>
{
public:
	FErrorNotificationCommandList()
		: TCommands<FErrorNotificationCommandList>(TEXT("ErrorNotificationCommandList"), LOCTEXT("ErrorNotificationCommandList", "Error Notification Command Test"), NAME_None, FErrorNotificationStyle::Get().GetStyleSetName())
	{}

	virtual void RegisterCommands() override
	{
		UI_COMMAND( FirstCommandInfo, "First Test", "This is the first test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SecondCommandInfo, "Second Test", "This is the second test menu item. Shows a keybinding", EUserInterfaceActionType::ToggleButton, FInputChord( ) );

		UI_COMMAND( ThirdCommandInfo, "Third Test", "This is the thrid test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( FourthCommandInfo, "Fourth Test", "This is the fourth test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
	}
	
public:
	TSharedPtr<FUICommandInfo> FirstCommandInfo;
	TSharedPtr<FUICommandInfo> SecondCommandInfo;
	TSharedPtr<FUICommandInfo> ThirdCommandInfo;
	TSharedPtr<FUICommandInfo> FourthCommandInfo;
	
};

class FMenus
{
public:
	static void FillMenu1Entries( FMenuBuilder& MenuBuilder )
	{
		MenuBuilder.BeginSection("Menu1Entries");
		{
			MenuBuilder.AddSubMenu( LOCTEXT("SubMenu", "Sub Menu"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
		}
		MenuBuilder.EndSection();
	}

	static void FillSubMenuEntries( FMenuBuilder& MenuBuilder )
	{
		MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().FirstCommandInfo );
		MenuBuilder.AddMenuEntry( FErrorNotificationCommandList::Get().SecondCommandInfo );
		MenuBuilder.AddSubMenu( LOCTEXT("SubMenu", "Sub Menu"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
		MenuBuilder.AddSubMenu( LOCTEXT("SubMenu2IsALittleLonger", "Sub Menu 2 is a little longer"), LOCTEXT("OpensASubmenu", "Opens a submenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillSubMenuEntries ) );
	}
};

TArray<bool> FErrorNotificationModule::ButtonStates;

void FErrorNotificationModule::StartupModule()
{
	ButtonStates.Reset();
	ButtonStates.AddZeroed(4);
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FErrorNotificationModule::OnPostEngineInit);
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	
	// MenuExtender->AddMenuBarExtension(
	// 	"Window",
	// 	EExtensionHook::After,
	// 	nullptr,
	// 	FMenuBarExtensionDelegate::CreateRaw(this, &FErrorNotificationModule::MakePulldownMenu));

	// const IWorkspaceMenuStructure& MenuStructure = WorkspaceMenu::GetMenuStructure();
	// TSharedRef<FWorkspaceItem> ContentBrowserGroup = MenuStructure.GetToolsCategory()->AddGroup(
	// 	FText::FromString(TEXT("XXX")),
	// 	FText::FromString(TEXT("YYY")),
	// 	FSlateIcon());
	//
	// ContentBrowserGroup->AddGroup(FText::FromString(TEXT("PPP")));
	//
	// auto a = FGlobalTabmanager::Get();
	// FGlobalTabmanager::Get()->RegisterTabSpawner( TEXT("PPP"), nullptr )
	// .SetDisplayName(FText::FromString(TEXT("333")))
	// .SetTooltipText( LOCTEXT( "ContentBrowserMenuTooltipText", "Open a Content Browser tab." ) )
	// .SetGroup( ContentBrowserGroup );

	MenuExtender->AddMenuBarExtension(
		"Window",
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FErrorNotificationModule::MakePulldownMenu));
	
	// MenuBarBuilder.AddPullDownMenu(
	// 	NSLOCTEXT("FErrorNotificationModule", "WindowMenuLabel", "MyLabel"),
	// 	FText::GetEmpty(),
	// 	FNewMenuDelegate::CreateSP(a, &FTabManager::PopulateTabSpawnerMenu, MyTestSuiteMenu::MenuRoot));
	

	// FGlobalTabmanager::Get()->RegisterNomadTabSpawner( TEXT("PPP"), nullptr )
	// .SetDisplayName(FText::FromString(TEXT("333")))
	// .SetTooltipText( LOCTEXT( "ContentBrowserMenuTooltipText", "Open a Content Browser tab." ) )
	// .SetGroup( ContentBrowserGroup );
	

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FErrorNotificationModule::ShutdownModule()
{
	
}

void FErrorNotificationModule::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
	FErrorNotificationStyle::ResetToDefault();
	FErrorNotificationCommandList::Register();
	CommandList = MakeShareable(new FUICommandList);

	struct Local
	{
		static bool IsButtonEnabled( int32 ButtonIndex )
		{
			return true;
		}

		static void OnButtonPressed( int32 ButtonIndex )
		{
			const bool NewState = !ButtonStates[ ButtonIndex ];
			ButtonStates[ ButtonIndex ] = NewState;
		}

		static bool IsButtonChecked( int32 ButtonIndex )
		{
			return ButtonStates[ ButtonIndex ];
		}

		
	};
	
	CommandList->MapAction(
		FErrorNotificationCommandList::Get().FirstCommandInfo,
		FExecuteAction::CreateStatic(&Local::OnButtonPressed, 0),
		FCanExecuteAction::CreateStatic(&Local::IsButtonEnabled, 0),
		FIsActionChecked::CreateStatic(&Local::IsButtonChecked, 0)
		);
	
	CommandList->MapAction(
	FErrorNotificationCommandList::Get().SecondCommandInfo,
	FExecuteAction::CreateStatic(&Local::OnButtonPressed, 1),
	FCanExecuteAction::CreateStatic(&Local::IsButtonEnabled, 1),
	FIsActionChecked::CreateStatic(&Local::IsButtonChecked, 1)
	);

	CommandList->MapAction(
	FErrorNotificationCommandList::Get().ThirdCommandInfo,
	FExecuteAction::CreateStatic(&Local::OnButtonPressed, 2),
	FCanExecuteAction::CreateStatic(&Local::IsButtonEnabled, 2),
	FIsActionChecked::CreateStatic(&Local::IsButtonChecked, 2)
	);

	CommandList->MapAction(
	FErrorNotificationCommandList::Get().FourthCommandInfo,
	FExecuteAction::CreateStatic(&Local::OnButtonPressed, 3),
	FCanExecuteAction::CreateStatic(&Local::IsButtonEnabled, 3),
	FIsActionChecked::CreateStatic(&Local::IsButtonChecked, 3)
	);
	menuBuilder.PushCommandList(CommandList.ToSharedRef());
	// FMenuBarBuilder MenuBarBuilder { CommandList };
	menuBuilder.AddPullDownMenu(LOCTEXT("Menu1", "Menu1"), LOCTEXT("OptionMenu", "OptionMenu"), FNewMenuDelegate::CreateStatic( &FMenus::FillMenu1Entries ));
	menuBuilder.AddPullDownMenu(LOCTEXT("Menu2", "Menu2"), LOCTEXT("OptionMenu2", "OptionMenu2"), FNewMenuDelegate::CreateRaw(this, &FErrorNotificationModule::FillSubmenu ));
	
	// menuBuilder.AddPullDownMenu(
	// FText::FromString("Example"),
	// FText::FromString("Open the Example menu"),
	// FNewMenuDelegate::CreateRaw(this, &FErrorNotificationModule::AddMenuEntry),
	// "Example",
	// FName(TEXT("ExampleMenu")));
}

void FErrorNotificationModule::AddMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection(TEXT("CustomMenu"), TAttribute(FText::FromString(TEXT("Category/Section Name"))));
	{
		MenuBuilder.AddSubMenu(FText::FromString(TEXT("My Submenu")),
			FText::FromString(TEXT("My submenu tooltip")),
				FNewMenuDelegate::CreateRaw(this, &FErrorNotificationModule::FillSubmenu));
	}
	MenuBuilder.EndSection();
	MenuBuilder.BeginSection(TEXT("CustomMenu"), TAttribute(FText::FromString(TEXT("Category/Section Name11"))));
	{
		MenuBuilder.AddSubMenu(FText::FromString(TEXT("My Submen111u")),
			FText::FromString(TEXT("My submenu tooltip111")),
				FNewMenuDelegate::CreateRaw(this, &FErrorNotificationModule::FillSubmenu));
	}
	MenuBuilder.EndSection();
}

void FErrorNotificationModule::FillSubmenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Menu Entry 1")),
		FText::FromString(TEXT("Menu Entry Tooltip 1")),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.CreateClassBlueprint"),
		FUIAction(FExecuteAction::CreateRaw(this, &FErrorNotificationModule::MenuCallback1))
		);

	MenuBuilder.AddMenuEntry(
	FText::FromString(TEXT("Menu Entry 2")),
	FText::FromString(TEXT("Menu Entry Tooltip 2")),
	FSlateIcon(),
	FUIAction(FExecuteAction::CreateRaw(this, &FErrorNotificationModule::MenuCallback2))
	);

	MenuBuilder.AddMenuEntry(
	FText::FromString(TEXT("Menu Entry 3")),
	FText::FromString(TEXT("Menu Entry Tooltip 3")),
	FSlateIcon(),
	FUIAction(FExecuteAction::CreateRaw(this, &FErrorNotificationModule::MenuCallback2))
	);
}

void FErrorNotificationModule::MenuCallback1()
{
	UE_LOG(LogErrorNoti, Log, TEXT("Action 1!"));
	
	FGlobalTabmanager::Get()->RegisterTabSpawner("ErrorLog", FOnSpawnTab::CreateRaw(this, &FErrorNotificationModule::SpawnTestSuite1));
	FGlobalTabmanager::Get()->RegisterTabSpawner("ErrorLog1", FOnSpawnTab::CreateRaw(this, &FErrorNotificationModule::SpawnTestSuite1));
	FGlobalTabmanager::Get()->RegisterTabSpawner("ErrorLog2", FOnSpawnTab::CreateRaw(this, &FErrorNotificationModule::SpawnTestSuite1));
	FGlobalTabmanager::Get()->RegisterTabSpawner("ErrorLog3", FOnSpawnTab::CreateRaw(this, &FErrorNotificationModule::SpawnTestSuite1));
	
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout( "SlateTestSuite_Layout" )
	->AddArea
	(
		FTabManager::NewArea(1600, 1200)
		->SetWindow( FVector2D(420, 10), false )
		->Split
		(
			FTabManager::NewStack()
			->AddTab( "ErrorLog", ETabState::OpenedTab )
			->SetForegroundTab(FName("ErrorLog"))
			->AddTab( "ErrorLog1", ETabState::OpenedTab )
			->AddTab( "ErrorLog2", ETabState::OpenedTab )
			->AddTab( "ErrorLog3", ETabState::OpenedTab )
		)		
	);


	FGlobalTabmanager::Get()->RestoreFrom( Layout, TSharedPtr<SWindow>() );
}

void FErrorNotificationModule::MenuCallback2()
{
	UE_LOG(LogErrorNoti, Log, TEXT("Action 2!"));
}

void FErrorNotificationModule::MenuCallback3()
{
	UE_LOG(LogErrorNoti, Log, TEXT("Action 3!"));
}

void FErrorNotificationModule::OnPostEngineInit()
{
	RegisterTabSpawner();
}

void FErrorNotificationModule::RegisterTabSpawner()
{
	// FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
	// "ErrorLog",
	// FOnSpawnTab::CreateRaw(this, &FErrorNotificationModule::SpawnTestSuite1 ) 
	// )
	// .SetDisplayName(NSLOCTEXT("UnrealEditor", "NiagaraDebuggerTab", "Niagara Debugger"))
	// .SetTooltipText(NSLOCTEXT("UnrealEditor", "NiagaraDebuggerTooltipText", "Open the Niagara Debugger Tab."))
	// .SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsDebugCategory())
	// .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.CreateClassBlueprint"));
}

TSharedRef<SDockTab> FErrorNotificationModule::SpawnTestSuite1( const FSpawnTabArgs& Args )
{
	//
	TSharedRef<SDockTab> TestSuite1Tab =
		SNew(SDockTab)
		. TabRole( ETabRole::MajorTab )
		. Label( LOCTEXT("TestSuite1TabLabel", "Test Suite 1") )
		. ToolTipText( LOCTEXT( "TestSuite1TabToolTip", "The App for the first Test Suite." ) );
	
	TestSuite1Tab->SetContent
	(
		SNew(SSplitter)
		.Orientation(Orient_Vertical)

		+ SSplitter::Slot()
		.Value(0.2f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("11")))
		]

		+ SSplitter::Slot()
		.Value(0.3f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("22")))
		]

		+ SSplitter::Slot()
		.Value(0.5f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("33")))
		]
	);

	return TestSuite1Tab;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FErrorNotificationModule, ErrorNotification)