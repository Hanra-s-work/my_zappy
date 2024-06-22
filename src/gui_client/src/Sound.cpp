/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Sound
*/

#include "Sound.hpp"

Sound::Sound()
{
}

bool Sound::loadSound(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        return false;
    }
    soundBuffers[name] = buffer;
    sounds[name].setBuffer(soundBuffers[name]);
    return true;
}

void Sound::playSound(const std::string& name, bool loop)
{
    if (sounds.find(name) != sounds.end()) {
        sounds[name].setLoop(loop);
        sounds[name].play();
    }
}

void Sound::stopSound(const std::string& name)
{
    if (sounds.find(name) != sounds.end()) {
        sounds[name].stop();
    }
}

bool Sound::loadMusic(const std::string& filename)
{
    return music.openFromFile(filename);
}

void Sound::playMusic()
{
    music.setLoop(true);
    music.play();
}

void Sound::stopMusic()
{
    music.stop();
}
