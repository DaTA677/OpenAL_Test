#include "SoundSource.h"
#include"SoundErrorReport.h"
#include<AL/alc.h>
SoundSource::SoundSource()
{
	Reset();
	alGenSources(1, &mSourceBuffer);
	alSourcefv(mSourceBuffer, AL_POSITION, (float*)mPosition);
	alSourcefv(mSourceBuffer, AL_VELOCITY, (float*)mVelocity);
	alSourcef(mSourceBuffer, AL_PITCH, mPitch);
	alSourcef(mSourceBuffer, AL_GAIN, mGain);
	alSourcei(mSourceBuffer, AL_LOOPING, mIsLooping);
}
SoundSource::~SoundSource() {
	alDeleteSources(1, &mSourceBuffer);
}

void SoundSource::Reset() {
	mPitch = 1.0f;
	mGain = 1.0f;
	mMaxDistance = 50.0f;
	mIsLooping = false;
	mSourceBuffer = 0;
	mSoundBuffer = 0;
	mPriority = SoundPriority::SOUNDPRIORITY_LOW;
}

void SoundSource::UpdateSoundSourceProperties()
{
	alSourcef(mSourceBuffer, AL_PITCH, mPitch);
	alSourcef(mSourceBuffer, AL_GAIN, mGain);
	alSourcei(mSourceBuffer, AL_LOOPING, mIsLooping);
}

void SoundSource::UpdateSoundSourcePhysics()
{
	alSourcefv(mSourceBuffer, AL_POSITION, (float*)mPosition);
	alSourcefv(mSourceBuffer, AL_VELOCITY, (float*)mVelocity);
}

bool SoundSource::isPlaying()
{
	ALint sourceState;
	alGetSourcei(mSourceBuffer, AL_SOURCE_STATE, &sourceState);
	return sourceState == AL_PLAYING;
}

void SoundSource::Play(ALuint bufferToPlay) {
	if (mSoundBuffer != bufferToPlay) {
		mSoundBuffer = bufferToPlay;
		alSourcei(mSourceBuffer, AL_BUFFER, mSoundBuffer);
	}

	if (isPlaying()) return;
	alSourcePlay(mSourceBuffer);
}

void SoundSource::Pause() {
	if (isPlaying()) alSourcePause(mSoundBuffer);
}
void SoundSource::Stop() {
	if (isPlaying()) alSourceStop(mSoundBuffer);
}