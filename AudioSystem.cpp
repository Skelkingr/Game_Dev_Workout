#include "AudioSystem.h"

#include <fmod_studio.hpp>
#include <fmod_errors.h>

#include <SDL/SDL_log.h>

#include <vector>

AudioSystem::AudioSystem(Game* game)
    :
    mGame(game),
    mSystem(nullptr),
    mLowLevelSystem(nullptr),
    mBanks({}),
    mEvents({})
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

void AudioSystem::ShutDown()
{
    mSystem->release();
}

void AudioSystem::Update(float deltaTime)
{
    mSystem->update();
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

void AudioSystem::PlayEvent(const std::string& name)
{
    auto iter = mEvents.find(name);
    if (iter != mEvents.end())
    {
        FMOD::Studio::EventInstance* event = nullptr;
        iter->second->createInstance(&event);
        if (event)
        {
            event->start();
            event->release();
        }
    }
}
