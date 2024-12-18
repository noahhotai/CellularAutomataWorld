#ifndef __SOUND_PLAYER_HPP__
#define __SOUND_PLAYER_HPP__


class SoundPlayer {
public:
    SoundPlayer() {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "Error initializing SDL audio: " << SDL_GetError() << std::endl;
            std::exit(2);
        }
    }

    ~SoundPlayer() {
        if (audioDevice != 0) {
            SDL_CloseAudioDevice(audioDevice);
            SDL_FreeWAV(audioData);
        }
        SDL_QuitSubSystem(SDL_INIT_AUDIO);  // Quit only audio subsystem
    }

    bool loadSound(const std::string& soundFile) {
        this->soundFile = soundFile;
        if (SDL_LoadWAV(soundFile.c_str(), &audioSpec, &audioData, &audioSize) == nullptr) {
            std::cerr << "Failed to load WAV file: " << SDL_GetError() << std::endl;
            return false;
        }
        originalAudioSize = audioSize;  // Store the original size of the audio data
        audioDevice = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
        if (audioDevice == 0) {
            std::cerr << "Failed to open audio device: " << SDL_GetError() << std::endl;
            SDL_FreeWAV(audioData);
            return false;
        }
        return true;
    }

    void playSound() const {
        if (audioDevice != 0) {
            SDL_ClearQueuedAudio(audioDevice);
            SDL_QueueAudio(audioDevice, audioData, audioSize);
            SDL_PauseAudioDevice(audioDevice, 0);  // Start playback
        }
    }

    std::shared_ptr<SoundPlayer> duplicate(){
        auto newSoundPlayerPtr = std::make_shared<SoundPlayer>();
        newSoundPlayerPtr->loadSound(soundFile);
        return newSoundPlayerPtr;
    }

    void pauseSound(bool pause) const {
        if (audioDevice != 0) {
            SDL_PauseAudioDevice(audioDevice, pause ? 1 : 0);  // Pause or resume playback
        }
    }

    bool isSoundNotFinished() const {
        if (audioDevice != 0) {
            return SDL_GetQueuedAudioSize(audioDevice) > 0;
        }
        return false;
    }

    Uint32 getBytesRemaining() const {
        if (audioDevice != 0) {
            return SDL_GetQueuedAudioSize(audioDevice);
        }
        return 0;
    }

    Uint32 getOriginalBytes() const {
        return originalAudioSize;
    }

    std::string soundFile;
private:
    SDL_AudioSpec audioSpec{};
    Uint8* audioData = nullptr;
    Uint32 audioSize = 0;
    Uint32 originalAudioSize = 0;  // Store the original size of the audio data
    SDL_AudioDeviceID audioDevice = 0;
};

#endif
