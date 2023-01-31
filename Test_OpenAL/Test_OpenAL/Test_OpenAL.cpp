// Test_OpenAL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<AL/al.h>
#include<AL/alc.h>
#include <string>
#include "Sound.h"


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

int main()
{

	const ALCchar* defaultDeviceString = alcGetString(/*device*/ nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
	ALCdevice* device = alcOpenDevice(defaultDeviceString);
	if (!device) {
		std::cerr << "Failed to get the Default device for OpenAL" << std::endl;
	}
	std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;

	ALCcontext* context = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context)) {
		std::cerr << "Failed to make the OpenAL context the curent context" << std::endl;
	}

	alec(alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f));
	alec(alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f));
	ALfloat forwardAndUpVectors[] = {
		/*forward = */ 1.0f,0.0f,0.0f,
		/*up = */ 0.0f,1.0f,0.0f
	};

	alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));

	std::string name = "H:\\Solutions\\OpenAL-soft test\\Test\\Test_OpenAL\\Sounds\\random1.wav";
	std::string extension = name.substr(name.length() - 3, 3);
	ALuint buffer = 0;
	if (extension == "wav") {
		Sound* s = new Sound();
		s->LoadFromWAV(name);
		alGenBuffers(1, &buffer);
		alBufferData(buffer, s->GetOALFormat(), s->GetData(), s->GetSize(), (ALsizei)s->GetFrequency());
	}
	std::cout << "Hello World!\n";

	ALuint monoSource;

	alec(alGenSources(1, &monoSource));
	alec(alSource3f(monoSource, AL_POSITION, 1.0f, 0.0f, 0.0f));
	alec(alSource3f(monoSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f));
	alec(alSourcef(monoSource, AL_PITCH, 0.5f));
	alec(alSourcef(monoSource, AL_GAIN, 1.0f));
	alec(alSourcei(monoSource, AL_LOOPING, AL_FALSE));
	alec(alSourcei(monoSource, AL_BUFFER, buffer));

	alec(alSourcePlay(monoSource));
	ALint sourceState;
	alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
	while (sourceState == AL_PLAYING) {
		alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
	}
	

	std::cout<< "Played!\n";
	alec(alDeleteSources(1, &monoSource));
	alec(alDeleteBuffers(1, &buffer));

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
