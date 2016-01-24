//
//  AudioEngine.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 16.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "AudioEngine.hpp"

#include "Types.hpp"

/**
 * Pauses Music
 */
void AudioEngine::pauseMusic() {
    Mix_PauseMusic();
}

/**
 * Resumes music after pause or plays again if the playback ended
 */
void AudioEngine::playMusic() {
    // Only resume if there's music
    if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
}

/**
 * Plays Music from file
 */
void AudioEngine::playMusic(std::string filepath) {
    
}

/**
 * Play Music from file and repeats forever
 */
void AudioEngine::playMusic(std::string filepath, bool repeat) {
    m_Music = Mix_LoadMUS(filepath.c_str());
    if (Mix_PlayingMusic() == 0) {
        // Play the music
        Mix_PlayMusic(m_Music, repeat ? -1 : 1);
    }
}

/**
 * Plays an effect from file
 */
void AudioEngine::playEffect(std::string filepath) {
    auto chunk = Mix_LoadWAV(filepath.c_str());
    auto usedChannel = Mix_PlayChannel(-1, chunk, 0);
    FELog("AudioEngine::playEffect() - Used Channel: " << std::to_string(usedChannel));
}



std::string getFileExtension(const std::string& filename) {
    if(filename.find_last_of(".") != std::string::npos)
        return filename.substr(filename.find_last_of(".")+1);
    return "";
}
