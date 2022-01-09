#include "ErrorNotificationStyle.h"
#include "Brushes/SlateBorderBrush.h"
#include "Brushes/SlateBoxBrush.h"
#include "Brushes/SlateImageBrush.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateStyleRegistry.h"

#if !UE_BUILD_SHIPPING

TSharedPtr< ISlateStyle > FErrorNotificationStyle::Instance = nullptr;

void FErrorNotificationStyle::ResetToDefault()
{
	SetStyle(FErrorNotificationStyle::Create());
}

void FErrorNotificationStyle::SetStyle(const TSharedRef<ISlateStyle>& NewStyle)
{
	if ( Instance.IsValid() )
	{
		FSlateStyleRegistry::UnRegisterSlateStyle( *Instance.Get() );
	}

	Instance = NewStyle;

	if ( Instance.IsValid() )
	{
		FSlateStyleRegistry::RegisterSlateStyle( *Instance.Get() );
	}
	else
	{
		ResetToDefault();
	}
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

TSharedRef<ISlateStyle> FErrorNotificationStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable( new FSlateStyleSet("ErrorNotificationStyle") );
	static FString ContentDir = FPaths::ProjectPluginsDir() / TEXT("ErrorNotification") / TEXT("Content");
	Style->SetContentRoot( ContentDir );

	// Note, these sizes are in Slate Units.
	// Slate Units do NOT have to map to pixels.
	const FVector2D Icon5x16(5.0f, 16.0f);
	const FVector2D Icon8x4(8.0f, 4.0f);
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon10x10(10.0f, 10.0f);
	const FVector2D Icon12x12(12.0f, 12.0f);
	const FVector2D Icon12x16(12.0f, 16.0f);
	const FVector2D Icon14x14(14.0f, 14.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon22x22(22.0f, 22.0f);
	const FVector2D Icon24x24(24.0f, 24.0f);
	const FVector2D Icon25x25(25.0f, 25.0f);
	const FVector2D Icon32x32(32.0f, 32.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);
	const FVector2D Icon36x24(36.0f, 24.0f);
	const FVector2D Icon128x128(128.0f, 128.0f);

	// Normal Text
	const FTextBlockStyle NormalText = FTextBlockStyle()
		.SetFont( DEFAULT_FONT("Regular", 9) )
		.SetColorAndOpacity(FSlateColor::UseForeground())
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor( FLinearColor( 0.02f, 0.3f, 0.0f ) )
		.SetHighlightShape( BOX_BRUSH("Common/TextBlockHighlightShape", FMargin(3.f/8.f) ) );
	
	// Testing images in the multi box test
	{
		Style->Set( "ErrorNotificationCommandList.FirstCommandInfo", new IMAGE_BRUSH( "Icon/BrushWireframe", Icon16x16 ) );
		Style->Set( "ErrorNotificationCommandList.SecondCommandInfo", new IMAGE_BRUSH( "Icon/Wireframe", Icon16x16 ) );
		Style->Set( "ErrorNotificationCommandList.ThirdCommandInfo", new IMAGE_BRUSH( "Icon/Unlit", Icon16x16 ) );
		Style->Set( "ErrorNotificationCommandList.FourthCommandInfo", new IMAGE_BRUSH( "Icon/Lit", Icon16x16 ) );
	}

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef DEFAULT_FONT

#endif
