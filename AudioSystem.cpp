#include "AudioSystem.h"

#include "Game.h"
#include "SoundEvent.h"

#include <fmod_studio.hpp>
#include <fmod_errors.h>

#include <SDL/SDL_log.h>

#include <vector>

namespace
{
    FMOD_VECTOR VecToFMOD(const Vector3& in)
    {
        FMOD_VECTOR vec = {};
        vec.x = in.y;
        vec.y = in.z;
        vec.z = in.x;

        return vec;
    }
}

unsigned int AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game)
    :
    mGame(game),
    mBanks({}),
    mEvents({}),
    mEventInstances({}),
    mBuses({}),
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

    LoadBank("Audio Banks/Master Bank.strings.bank");
    LoadBank("Audio Banks/Master Bank.bank");

    return true;
}

void AudioSystem::Shutdown()
{
    UnloadAllBanks();
    if (mSystem)
    {
        mSystem->release();
    }
}

void AudioSystem::Update(float deltaTime)
{
    std::vector<unsigned int> done;

    for (auto& iter : mEventInstances)
    {
        FMOD::Studio::EventInstance* e = iter.second;

        FMOD_STUDIO_PLAYBACK_STATE state;
        e->getPlaybackState(&state);
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
        {
            e->release();
            done.emplace_back(iter.first);
        }
    }

    for (auto id : done)
    {
        mEventInstances.erase(id);
    }

    mSystem->update();
}

void AudioSystem::SetListener(const Matrix4& viewMatrix)
{
    Matrix4 invView = viewMatrix;
    invView.Invert();

    FMOD_3D_ATTRIBUTES listener = {};
    listener.position = VecToFMOD(invView.GetTranslation());
    listener.forward = VecToFMOD(invView.GetZAxis());
    listener.up = VecToFMOD(invView.GetYAxis());

    listener.velocity = { 0.0f, 0.0f, 0.0f };

    mSystem->setListenerAttributes(0, &listener);
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
    FMOD::Studio::EventInstance* event = nullptr;

    auto iter = mEventInstances.find(id);
    if (iter != mEventInstances.end())
    {
        event = iter->second;
    }

    return event;
}

void AudioSystem::LoadBank(const std::string& name)
{
    if (mBanks.find(name) != mBanks.end())
    {
        return;
    }

    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = mSystem->loadBankFile(
        name.c_str(),
        FMOD_STUDIO_LOAD_BANK_NORMAL,
        &bank
    );

    const int maxPathLength = 512;
    if (result == FMOD_OK)
    {
        mBanks.emplace(name, bank);

        bank->loadSampleData();

        int numEvents = 0;
        bank->getEventCount(&numEvents);
        if (numEvents > 0)
        {
            std::vector<FMOD::Studio::EventDescription*> events(numEvents);
            bank->getEventList(events.data(), numEvents, &numEvents);
            
            char eventName[maxPathLength] = {};
            for (int i = 0; i < numEvents; i++)
            {
                FMOD::Studio::EventDescription* e = events[i];
                e->getPath(eventName, maxPathLength, nullptr);
                mEvents.emplace(eventName, e);
            }
        }
    }
}

void AudioSystem::UnloadBank(const std::string& name)
{
    auto iter = mBanks.find(name);
    if (iter == mBanks.end())
    {
        return;
    }

    FMOD::Studio::Bank* bank = iter->second;

    int numEvents = 0;
    bank->getEventCount(&numEvents);
    if (numEvents > 0)
    {
        std::vector<FMOD::Studio::EventDescription*> events(numEvents);
        bank->getEventList(events.data(), numEvents, &numEvents);
        
        char eventName[512] = {};
        for (int i = 0; i < numEvents; i++)
        {
            FMOD::Studio::EventDescription* e = events[i];
            e->getPath(eventName, 512, nullptr);

            auto eventi = mEvents.find(eventName);
            if (eventi != mEvents.end())
            {
                mEvents.erase(eventi);
            }
        }
    }

    int numBuses = 0;
    bank->getBusCount(&numBuses);
    if (numBuses > 0)
    {
        std::vector<FMOD::Studio::Bus*> buses(numBuses);
        bank->getBusList(buses.data(), numBuses, &numBuses);

        char busName[512] = {};
        for (int i = 0; i < numBuses; i++)
        {
            FMOD::Studio::Bus* bus = buses[i];
            bus->getPath(busName, 512, nullptr);

            auto busi = mBuses.find(busName);
            if (busi != mBuses.end())
            {
                mBuses.erase(busi);
            }
        }
    }

    bank->unloadSampleData();
    bank->unload();

    mBanks.erase(iter);
}

void AudioSystem::UnloadAllBanks()
{
    for (auto& iter : mBanks)
    {
        iter.second->unloadSampleData();
        iter.second->unload();
    }

    mBanks.clear();
    mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
    unsigned int retID = 0;

    auto iter = mEvents.find(name);
    if (iter != mEvents.end())
    {
        FMOD::Studio::EventInstance* event = nullptr;
        iter->second->createInstance(&event);
        if (event)
        {
            event->start();

            sNextID++;
            retID = sNextID;

            mEventInstances.emplace(retID, event);
        }
    }

    return SoundEvent(this, retID);
}
