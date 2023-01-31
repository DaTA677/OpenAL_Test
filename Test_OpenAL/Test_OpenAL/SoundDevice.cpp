#include "SoundDevice.h"
#include <AL/al.h>
#include <AL/alc.h>

SoundDevice* SoundDevice::get() {
	static SoundDevice* s_snd_device = new SoundDevice();
	return s_snd_device;
}

SoundDevice::SoundDevice() {
	const ALCchar* defaultDeviceString = alcGetString(/*device*/ nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
	mALCDevice = alcOpenDevice(defaultDeviceString);
	if (!mALCDevice) {
		throw("Failed to get the Default device for OpenAL");
	}
	

	
	
}

SoundDevice::~SoundDevice() {
	if (!alcMakeContextCurrent(nullptr))
		throw("Failed to set context to nullptr");

}