#pragma once
#include<vector>
#include"SoundSource.h"
#include"SoundDevice.h"
#include<map>

class SoundSystem
{
public:
	static SoundSystem* get();
	static void DestroySoundSystem(SoundSystem* s);

	void Update(float mSec);
	void PlaySounds();


protected:
	SoundSystem();
	~SoundSystem();


	SoundDevice* mSndDevice;
	std::vector<SoundSource*> mSources;
	std::map<std::string, ALuint> mSounds;

	float mListenerGain;
	float mListenerPosition[3];
	float mListenerVelocity[3];


};

