#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/**
 * @brief Clase encargada de la gestión de audio del juego
 * 
 * Maneja la carga, reproducción y control de música
 * y efectos de sonido.
 */
class AudioManager {
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, sf::Music> musicTracks;
    sf::Music* currentMusic;
    bool isMusicEnabled;
    bool areSoundEffectsEnabled;
    float musicVolume;
    float soundVolume;
    
public:
    AudioManager();
    ~AudioManager();
    
    // Métodos de inicialización (verbos)
    bool Initialize();
    bool LoadAudioAssets();
    void Cleanup();
    
    // Métodos de música
    void PlayMusic(const std::string& musicName, bool loop = true);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();
    
    // Métodos de efectos de sonido
    void PlaySoundEffect(const std::string& soundName);
    void StopSoundEffect(const std::string& soundName);
    void StopAllSoundEffects();
    
    // Métodos de carga
    bool LoadSoundEffect(const std::string& name, const std::string& filename);
    bool LoadMusic(const std::string& name, const std::string& filename);
    void UnloadSoundEffect(const std::string& soundName);
    void UnloadMusic(const std::string& musicName);
    
    // Métodos de control de volumen
    void SetMusicVolume(float volume);
    void SetSoundVolume(float volume);
    void IncreaseMusicVolume(float increment = 10.0f);
    void DecreaseMusicVolume(float decrement = 10.0f);
    void IncreaseSoundVolume(float increment = 10.0f);
    void DecreaseSoundVolume(float decrement = 10.0f);
    
    // Métodos de habilitación/deshabilitación
    void EnableMusic();
    void DisableMusic();
    void EnableSoundEffects();
    void DisableSoundEffects();
    void ToggleMusic();
    void ToggleSoundEffects();
    
    // Getters
    bool IsMusicEnabled() const { return isMusicEnabled; }
    bool AreSoundEffectsEnabled() const { return areSoundEffectsEnabled; }
    float GetMusicVolume() const { return musicVolume; }
    float GetSoundVolume() const { return soundVolume; }
    bool IsMusicPlaying() const;
    
    // Setters
    void SetMusicEnabled(bool enabled) { isMusicEnabled = enabled; }
    void SetSoundEffectsEnabled(bool enabled) { areSoundEffectsEnabled = enabled; }
    
private:
    // Métodos privados auxiliares
    bool LoadGameSounds();
    bool LoadGameMusic();
    void ValidateVolume(float& volume);
    std::string GetFullAudioPath(const std::string& filename) const;
};

#endif // AUDIO_MANAGER_HPP