#pragma once

#if !UE_BUILD_SHIPPING

class ISlateStyle;

class FErrorNotificationStyle
{
public:
	static TSharedRef<ISlateStyle> Create();

	/** @return the singleton instance. */
	static const ISlateStyle& Get()
	{
		return *( Instance.Get() );
	}

	static void ResetToDefault();

private:

	static void SetStyle( const TSharedRef< ISlateStyle >& NewStyle );

private:

	/** Singleton instances of this style. */
	static TSharedPtr< ISlateStyle > Instance;
	
	
};


#endif