#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager() 
    : isMusicEnabled(true), areSoundEffectsEnabled(true), 
      musicVolume(50.0f), soundVolume(50.0f) {
}

AudioManager::~AudioManager() {
    Cleanup();
}

bool AudioManager::Initialize() {
    // SFML Audio no requiere inicialización explícita
    // Solo verificamos que podamos cargar los recursos
    return LoadAudioAssets();
}

bool AudioManager::LoadAudioAssets() {
    return LoadGameSounds() && LoadGameMusic();
}

void AudioManager::Cleanup() {
    // SFML maneja automáticamente la limpieza de recursos
    sounds.clear();
    soundBuffers.clear();
    musicTracks.clear();
}

void AudioManager::PlayMusic(const std::string& musicName, bool loop) {
    if (!isMusicEnabled) return;
    
    auto it = musicTracks.find(musicName);
    if (it != musicTracks.end()) {
        it->second.setLoop(loop);
        it->second.setVolume(musicVolume);
        it->second.play();
        currentMusic = &(it->second);
    }
}

void AudioManager::StopMusic() {
    for (auto& pair : musicTracks) {
        pair.second.stop();
    }
}

void AudioManager::PauseMusic() {
    for (auto& pair : musicTracks) {
        pair.second.pause();
    }
}

void AudioManager::ResumeMusic() {
    for (auto& pair : musicTracks) {
        if (pair.second.getStatus() == sf::Music::Paused) {
            pair.second.play();
        }
    }
}

void AudioManager::PlaySoundEffect(const std::string& soundName) {
    if (!areSoundEffectsEnabled) return;
    
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        it->second.setVolume(soundVolume);
        it->second.play();
    }
}

void AudioManager::StopSoundEffect(const std::string& soundName) {
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        it->second.stop();
    }
}

void AudioManager::StopAllSoundEffects() {
    for (auto& pair : sounds) {
        pair.second.stop();
    }
}

bool AudioManager::LoadSoundEffect(const std::string& soundName, const std::string& filename) {
    std::string fullPath = GetFullAudioPath(filename);
    
    // Crear el soundBuffer para este sonido
    auto bufferIt = soundBuffers.emplace(soundName, sf::SoundBuffer()).first;
    
    if (!bufferIt->second.loadFromFile(fullPath)) {
        std::cerr << "Failed to load sound effect: " << filename << std::endl;
        soundBuffers.erase(bufferIt);
        return false;
    }
    
    // Crear el objeto Sound y asociarlo con el buffer
    sounds[soundName].setBuffer(bufferIt->second);
    return true;
}

bool AudioManager::LoadMusic(const std::string& musicName, const std::string& filename) {
    std::string fullPath = GetFullAudioPath(filename);
    
    // sf::Music no es copiable, necesitamos usar emplace con construcción in-place
    auto result = musicTracks.try_emplace(musicName);
    if (!result.second) {
        // Ya existe, reemplazar
        musicTracks.erase(musicName);
        result = musicTracks.try_emplace(musicName);
    }
    
    if (!result.first->second.openFromFile(fullPath)) {
        std::cerr << "Failed to load music: " << filename << std::endl;
        musicTracks.erase(result.first);
        return false;
    }
    
    return true;
}

void AudioManager::UnloadSoundEffect(const std::string& soundName) {
    sounds.erase(soundName);
    soundBuffers.erase(soundName);
}

void AudioManager::UnloadMusic(const std::string& musicName) {
    musicTracks.erase(musicName);
}

void AudioManager::SetMusicVolume(float volume) {
    ValidateVolume(volume);
    musicVolume = volume;
    for (auto& pair : musicTracks) {
        pair.second.setVolume(musicVolume);
    }
}

void AudioManager::SetSoundVolume(float volume) {
    ValidateVolume(volume);
    soundVolume = volume;
    for (auto& pair : sounds) {
        pair.second.setVolume(soundVolume);
    }
}

void AudioManager::IncreaseMusicVolume(float increment) {
    SetMusicVolume(musicVolume + increment);
}

void AudioManager::DecreaseMusicVolume(float decrement) {
    SetMusicVolume(musicVolume - decrement);
}

void AudioManager::IncreaseSoundVolume(float increment) {
    SetSoundVolume(soundVolume + increment);
}

void AudioManager::DecreaseSoundVolume(float decrement) {
    SetSoundVolume(soundVolume - decrement);
}

void AudioManager::EnableMusic() {
    isMusicEnabled = true;
}

void AudioManager::DisableMusic() {
    isMusicEnabled = false;
    StopMusic();
}

void AudioManager::EnableSoundEffects() {
    areSoundEffectsEnabled = true;
}

void AudioManager::DisableSoundEffects() {
    areSoundEffectsEnabled = false;
    StopAllSoundEffects();
}

void AudioManager::ToggleMusic() {
    if (isMusicEnabled) {
        DisableMusic();
    } else {
        EnableMusic();
    }
}

void AudioManager::ToggleSoundEffects() {
    if (areSoundEffectsEnabled) {
        DisableSoundEffects();
    } else {
        EnableSoundEffects();
    }
}

bool AudioManager::IsMusicPlaying() const {
    for (const auto& pair : musicTracks) {
        if (pair.second.getStatus() == sf::Music::Playing) {
            return true;
        }
    }
    return false;
}

// Métodos privados
bool AudioManager::LoadGameSounds() {
    LoadSoundEffect("eat", "comer.wav");
    LoadSoundEffect("crash", "choque.wav");
    LoadSoundEffect("gameover", "gameover.wav");
    LoadSoundEffect("start", "inicio.wav");
    
    return true; // Permitir que funcione sin archivos de audio
}

bool AudioManager::LoadGameMusic() {
    LoadMusic("background", "musica_fondo.wav");
    
    return true;
}

void AudioManager::ValidateVolume(float& volume) {
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 100.0f) volume = 100.0f;
}

std::string AudioManager::GetFullAudioPath(const std::string& filename) const {
    return "assets/music/" + filename;
}