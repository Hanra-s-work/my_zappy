/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Sound
*/

#ifndef SOUND_HPP_
    #define SOUND_HPP_

    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <map>
    #include <string>
    #include <memory>

class Sound
{
    public:
        Sound();
        ~Sound();
        bool loadSound(const std::string &name, const std::string &filename);
        void playSound(const std::string &name, bool loop);
        void stopSound(const std::string &name);
        bool loadMusic(const std::string &filename);
        void playMusic();
        void stopMusic();
        void increaseSoundVolume(const std::string &name, float amount);
        void decreaseSoundVolume(const std::string &name, float amount);
        float getSoundVolume(const std::string &name) const;
        void increaseMusicVolume(float amount);
        void decreaseMusicVolume(float amount);
        float getMusicVolume() const;
        void setSoundVolume(const std::string &name, float volume);

    private:
        sf::Music music;
        bool loop = false;
        float amount = 5.0f;
        std::map<std::string, sf::SoundBuffer> soundBuffers;
        std::map<std::string, sf::Sound> sounds;
};

class VolumeVisualizer
{
    public:
        VolumeVisualizer(float width, float height);

        void setVolume(float volume);
        void draw(sf::RenderWindow &window);
        void manageVolume(std::unique_ptr<Sound> &sound);

    private:
        sf::RectangleShape backgroundBar;
        sf::RectangleShape volumeBar;
        float maxWidth;
        std::map<std::string, float> soundVolumes;

        void drawSoundVolumes(sf::RenderWindow &window);
};

#endif /* !SOUND_HPP_ */
