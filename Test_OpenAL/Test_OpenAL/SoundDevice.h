#pragma once
#include<AL/al.h>
#include<AL/alc.h>
#include <iostream>

#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError(); \
	if (error != AL_NO_ERROR)\
	{\
	std::cerr << "OpenAL Error:" << error << " with call for " << #message << std::endl;\
		}\
}

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)


class SoundDevice
{
public:
	static SoundDevice* get();
private:
	SoundDevice();
	~SoundDevice();

	ALCdevice* mALCDevice;
	ALCcontext* mALCContext;

};

