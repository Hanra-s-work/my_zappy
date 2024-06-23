/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Sound
*/

#include "graphic/Sound.hpp"

Sound::Sound()
{
}

bool Sound::loadSound(const std::string &name, const std::string &filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        return false;
    }
    soundBuffers[name] = buffer;
    sounds[name].setBuffer(soundBuffers[name]);
    return true;
}

void Sound::playSound(const std::string &name, bool loop)
{
    if (sounds.find(name) != sounds.end()) {
        sounds[name].setLoop(loop);
        sounds[name].play();
    }
}

void Sound::stopSound(const std::string &name)
{
    if (sounds.find(name) != sounds.end()) {
        sounds[name].stop();
    }
}

bool Sound::loadMusic(const std::string &filename)
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

void Sound::increaseSoundVolume(const std::string &name, float amount)
{
    if (sounds.find(name) != sounds.end()) {
        float volume = sounds[name].getVolume();
        volume += amount;
        if (volume > 100.0f) {
            volume = 100.0f;
        }
        sounds[name].setVolume(volume);
    }
}

void Sound::decreaseSoundVolume(const std::string &name, float amount)
{
    if (sounds.find(name) != sounds.end()) {
        float volume = sounds[name].getVolume();
        volume -= amount;
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        sounds[name].setVolume(volume);
    }
}

float Sound::getSoundVolume(const std::string &name) const
{
    if (sounds.find(name) != sounds.end()) {
        return sounds.at(name).getVolume();
    }
    return 0.0f;
}

void Sound::increaseMusicVolume(float amount)
{
    float volume = music.getVolume();
    volume += amount;
    if (volume > 100.0f) {
        volume = 100.0f;
    }
    music.setVolume(volume);
}

void Sound::decreaseMusicVolume(float amount)
{
    float volume = music.getVolume();
    volume -= amount;
    if (volume < 0.0f) {
        volume = 0.0f;
    }
    music.setVolume(volume);
}

float Sound::getMusicVolume() const
{
    return music.getVolume();
}

void Sound::setSoundVolume(const std::string &name, float volume)
{
    if (sounds.find(name) != sounds.end()) {
        sounds[name].setVolume(volume);
    }
}

VolumeVisualizer::VolumeVisualizer(float width, float height)
    : maxWidth(width)
{
    backgroundBar.setSize(sf::Vector2f(width, height));
    backgroundBar.setFillColor(sf::Color(50, 50, 50));

    volumeBar.setSize(sf::Vector2f(width, height));
    volumeBar.setFillColor(sf::Color(100, 250, 50));
}

void VolumeVisualizer::setVolume(float volume)
{
    float width = (volume / 100.0f) * maxWidth;
    volumeBar.setSize(sf::Vector2f(width, backgroundBar.getSize().y));
}

void VolumeVisualizer::draw(sf::RenderWindow &window)
{
    window.draw(backgroundBar);
    window.draw(volumeBar);
}

void VolumeVisualizer::drawSoundVolumes(sf::RenderWindow &window)
{
    float y = backgroundBar.getPosition().y + backgroundBar.getSize().y + 10;
    for (const auto &soundVolume : soundVolumes) {
        sf::RectangleShape soundBar(sf::Vector2f(maxWidth, 20));
        soundBar.setPosition(backgroundBar.getPosition().x, y);
        soundBar.setFillColor(sf::Color(50, 50, 50));
        window.draw(soundBar);

        sf::RectangleShape volumeLevel(sf::Vector2f((soundVolume.second / 100.0f) * maxWidth, 20));
        volumeLevel.setPosition(backgroundBar.getPosition().x, y);
        volumeLevel.setFillColor(sf::Color(100, 250, 50));
        window.draw(volumeLevel);

        y += 30;
    }
}

void VolumeVisualizer::manageVolume(Sound &sound)
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Volume Control");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            sound.decreaseMusicVolume(1.0f);
            setVolume(sound.getMusicVolume());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            sound.increaseMusicVolume(1.0f);
            setVolume(sound.getMusicVolume());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            sound.decreaseSoundVolume("footsteps", 1.0f);
            soundVolumes["footsteps"] = sound.getSoundVolume("footsteps");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            sound.increaseSoundVolume("footsteps", 1.0f);
            soundVolumes["footsteps"] = sound.getSoundVolume("footsteps");
        }
        window.clear();
        draw(window);
        drawSoundVolumes(window);
        window.display();
    }
}
