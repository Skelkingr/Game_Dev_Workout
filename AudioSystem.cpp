#include "AudioSystem.h"

#include <fmod_studio.hpp>
#include <fmod_errors.h>

#include <SDL/SDL_log.h>

AudioSystem::AudioSystem(Game* game)
    :
    mGame(game),
    mSystem(nullptr),
    mLowLevelSystem(nullptr)
{}

bool AudioSystem::Initialize()
{
    FMOD::Debug_Initialize(
        FMOD_DEBUG_LEVEL_ERROR,
        FMOD_DEBUG_MODE_TTY
    );

    FMOD_RESULT result = FMOD::Studio::System::create(&mSystem);
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    result = mSystem->initialize(
        512,
        FMOD_STUDIO_INIT_NORMAL,
        FMOD_INIT_NORMAL,
        nullptr
    );
    if (result != FMOD_OK)
    {
        SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    mSystem->getLowLevelSystem(&mLowLevelSystem);

    return true;
}

void AudioSystem::ShutDown()
{
    mSystem->release();
}

void AudioSystem::Update(float deltaTime)
{
    mSystem->update();
}
