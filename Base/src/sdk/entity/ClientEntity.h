#pragma once
#include "ClientRenderable.h"
#include "ClientNetworkable.h"
#include "ClientThinkable.h"
#include "ClientUnknown.h"

#include "../classvars/SoundInfo.h"

class MouthInfo;
class ClientEntity : public ClientUnknown, public ClientRenderable, public ClientNetworkable, public ClientThinkable
{
	// Delete yourself.
	virtual void Release(void) = 0;

	// Network origin + angles
	virtual const Vector& GetAbsOrigin(void) const = 0;
	virtual const Vector& GetAbsAngles(void) const = 0;

	virtual MouthInfo* GetMouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool GetSoundSpatialization(SpatializationInfo& info) = 0;

	virtual bool IsBlurred(void) = 0;
};