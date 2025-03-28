#include "../Gury/Game/Services/soundservice.h"
#include "../Gury/Game/World/sounds.h"

void RBX::Sound::stop()
{
	channel->stop();
}

void RBX::Sound::setStartPosition(double value)
{
	double oldPosition = getStartPosition();
	double soundLength = getLength();
	double newPosition = fmod(value, (soundLength ? soundLength : 1.0));
	if (oldPosition != newPosition)
	{
		startPosition = newPosition * 1000.0f;
	}
}

void RBX::Sound::setEndPosition(double value)
{

}

void RBX::Sound::playOnce()
{
	if (!isPlaying())
	{
		play();
	}
}

void RBX::Sound::play()
{
	if (!sound)
	{
		SoundService::get()->mpSystem->createSound(soundPath.c_str(), 0, 0, &sound);
	}

	sound->setMode(FMOD_LOOP_OFF);
	SoundService::get()->mpSystem->playSound(sound, 0, 0, &channel);
	channel->setPosition(startPosition, FMOD_TIMEUNIT_MS);
	channel->setVolume(volume);
}