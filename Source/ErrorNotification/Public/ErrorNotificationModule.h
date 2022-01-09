// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Modules/ModuleInterface.h"
#include "CoreMinimal.h"

extern struct FLogCategoryLogErrorNoti : public FLogCategory<ELogVerbosity::Log, ELogVerbosity::All>
{ 
	FORCEINLINE FLogCategoryLogErrorNoti() : FLogCategory(TEXT("ErrorNotiLog")) {} 
} LogErrorNoti;

class FErrorNotificationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:
	void MakePulldownMenu(FMenuBarBuilder &menuBuilder);
	void AddMenuEntry(FMenuBuilder& MenuBuilder);
	void FillSubmenu(FMenuBuilder& MenuBuilder);
	void MenuCallback1();
	void MenuCallback2();
	void MenuCallback3();

private:
	void OnPostEngineInit();
	void RegisterTabSpawner();

private:
	TSharedRef<SDockTab> SpawnTestSuite1( const FSpawnTabArgs& Args );
	TSharedPtr<FUICommandList> CommandList;
	static TArray<bool> ButtonStates;

};
