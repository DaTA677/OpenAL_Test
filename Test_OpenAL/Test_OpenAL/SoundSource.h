#pragma once
#include<AL/al.h>

enum SoundPriority {
	SOUNDPRIORITY_LOW,
	SOUNDPRIORITY_MEDIUM,
	SOUNDPRIORITY_HIGH,
	SOUNDPRIORITY_ALWAYS
};
class SoundSource
{
public:
	SoundSource();
	~SoundSource();
	
	void Play(ALuint bufferToPlay);
	void Pause();
	void Stop();

	void Reset();

	void SetPitch(const float& pitch) { if(pitch>=0.0f) mPitch = pitch; }
	float GetPitch() const { return mPitch; }
	
	void SetGain(const float& gain) { mGain= gain; }
	float GetGain() const { return mGain; }
	
	void SetMaxDistance(const float& distance) { if(distance>=0.0f) mMaxDistance= distance; }
	float GetMaxDistance() const { return mMaxDistance; }

	void SetLooping(const bool& looping) { mIsLooping = looping; }
	bool IsLooping() const{ return mIsLooping; }

	ALuint GetSourceBuffer()const { return mSourceBuffer; }

	void SetPriority(SoundPriority priority) { mPriority = (SoundPriority)priority; }

	void UpdateSoundSourceProperties();
	void UpdateSoundSourcePhysics();

	bool isPlaying();

protected:
	float mPitch;
	float mGain;
	float mMaxDistance;

	float mPosition[3];
	float mVelocity[3];
	float mDirection[3];

	bool mIsLooping;
	float timeLeft;


	ALuint mSourceBuffer;
	ALuint mSoundBuffer;
	SoundPriority mPriority;



};

