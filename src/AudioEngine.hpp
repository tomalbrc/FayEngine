//
//  AudioEngine.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 16.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef AudioEngine_hpp
#define AudioEngine_hpp

#include <stdio.h>
#include "SDL_mixer.h"
#include <string>
#include <vector>

class AudioEngine {
public:
    /**
     * Pauses Music
     */
    void pauseMusic();

    /**
     * Resumes music after pause or plays again if the playback ended
     */
    void playMusic();

    /**
     * Plays Music from file
     *
     * @param filepath Path to the music file
     */
    void playMusic(std::string filepath);
    
    /**
     * Play Music from file with a flag wether to repaet forver or play once
     *
     * @param filepath Path to the sound-effect file
     * @param repeat flag
     */
    void playMusic(std::string filepath, bool repeat);
    
    /**
     * Plays an effect from file
     *
     * @param filepath Path to the sound-effect file
     */
    void playEffect(std::string filepath);
private:
    Mix_Music *m_Music = NULL;
    std::vector<Mix_Chunk> m_SoundEffects;
};

#endif /* AudioEngine_hpp */
