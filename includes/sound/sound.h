#pragma once

#include <raylib.h>
#include <string>

class SoundLoader {
    Sound current_sound;

    public:
        void Load(const std::string &path, float volume) {
            current_sound = LoadSound(path.c_str());
            SetSoundVolume(current_sound, volume);
            PlaySound(current_sound);
        }
        
        ~SoundLoader() {
            UnloadSound(current_sound);
        }
};