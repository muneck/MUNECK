#include "MediaPipePresenceObserverComponent.h"
#include "MediaPipePipelineComponent.h"
#include "MediaPipeShared.h"

#if PLATFORM_WINDOWS
UMediaPipePresenceObserverComponent::UMediaPipePresenceObserverComponent()
{
}

void UMediaPipePresenceObserverComponent::OnUmpPacket(IUmpObserver* Observer)
{
	if (!UmpCompareType<bool>(Observer))
	{
		//PLUGIN_LOG(Error, TEXT("Invalid Presence message"));
		return;
	}

	bPresent = UmpCastPacket<bool>(Observer->GetData());
	UpdateTimestamp();
}
#elif PLATFORM_ANDROID
UMediaPipePresenceObserverComponent::UMediaPipePresenceObserverComponent()
{}
void UMediaPipePresenceObserverComponent::OnUmpPacket(IUmpObserver* Observer)
{}
#endif