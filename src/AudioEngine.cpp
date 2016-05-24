//
//  AudioEngine.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 16.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "AudioEngine.hpp"
#include "Types.hpp"

FE_NAMESPACE_BEGIN

AudioEngine::AudioEngine() {
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024*4);
}

AudioEnginePtr AudioEngine::getInstance() {
    static AudioEnginePtr instance = std::make_shared<AudioEngine>();
    return instance;
}

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
    playMusic(filepath, false);
}

/**
 * Play Music from file and repeats forever
 */
void AudioEngine::playMusic(std::string filepath, bool repeat) {
    Mix_FreeMusic(m_Music);
    m_Music = Mix_LoadMUS(filepath.c_str());
    if (Mix_PlayingMusic() == 0) FELog("Warning: Playing music already! Continuing...");
    
    FELog("Playing \"" + filepath + "\"!");
    Mix_PlayMusic(m_Music, repeat ? -1 : 1);
}

/**
 * Plays an effect from file
 */
void AudioEngine::playEffect(std::string filepath) {
    playEffect(filepath, 0.5f);
}
void AudioEngine::playEffect(std::string filepath, float volume) {
    auto chunk = Mix_LoadWAV(filepath.c_str());
    SDL_assert_always(chunk != nullptr);
    Mix_VolumeChunk(chunk, MIX_MAX_VOLUME*volume);
    auto usedChannel = Mix_PlayChannel(-1, chunk, 0);
    FELog("AudioEngine::playEffect() - Used Channel: " << std::to_string(usedChannel));
}


std::string getFileExtension(const std::string& filename) {
    if(filename.find_last_of(".") != std::string::npos)
        return filename.substr(filename.find_last_of(".")+1);
    return "";
}


} // namespace FE
