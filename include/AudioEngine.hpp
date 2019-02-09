//
//  AudioEngine.hpp
//  rawket
//
//  Created by Tom Albrecht on 16.01.16.
//  
//

#ifndef AudioEngine_hpp
#define AudioEngine_hpp

#include <stdio.h>
#include <map>
#include "SDL_mixer.h"
#include "Types.hpp"

RKT_NAMESPACE_BEGIN

class AudioEngine;
RKT_create__ptr(AudioEngine);

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    static AudioEngine_ptr getInstance();
    
    /**
     * Pauses Music
     */
    void pauseMusic();

    /**
     * Resumes music after pause or plays again if the playback ended
     */
    void playMusic();

    /**
     * Plays Music from file without fade effect. Replaces the current playing music with the one from the file
     *
     * @param filepath Path to the music file
     */
    void playMusic(std::string filepath);
    
    /**
     * Plays music from file and fades that in with a set duration of time (See fadeInDuration param) and repeats if wanted
     *
     * @param fadeInDuration    Duration in ms to fade in effect to complete
     */
    void playMusic(std::string filepath, bool repeat, int fadeInDuration);
    
    /**
     * Play Music from file with a flag wether to repaet forver or play once
     *
     * @param filepath Path to the sound-effect file
     * @param repeat flag
     */
    void playMusic(std::string filepath, bool repeat);
    
    /**
     * Plays an effect from file with a specified volume.
     * The volume parameter ranges from 0.0 - 1.0
     *
     * @param filepath Path to the sound-effect file
     * @param volume Ranges from 0.0 to 1.0
     */
    void playEffect(std::string filepath, float volume);
    
    /**
     * Plays an effect from file with a volume of 0.5
     *
     * @param filepath Path to the sound-effect file
     */
    void playEffect(std::string filepath);

private:
    Mix_Music *m_Music = NULL;
    std::map<std::string, Mix_Chunk*> m_SoundEffects;
};

RKT_NAMESPACE_END
#endif /* AudioEngine_hpp */
