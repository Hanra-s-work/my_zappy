/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Sound
*/

#ifndef SOUND_HPP_
    #define SOUND_HPP_

    #include <SFML/Audio.hpp>
    #include <map>
    #include <string>

class Sound
{
    public:
        Sound();
        bool loadSound(const std::string& name, const std::string& filename);
        void playSound(const std::string& name, bool loop);
        void stopSound(const std::string& name);
        bool loadMusic(const std::string& filename);
        void playMusic();
        void stopMusic();

    private:
        sf::Music music;
        bool loop = false;
        std::map<std::string, sf::SoundBuffer> soundBuffers;
        std::map<std::string, sf::Sound> sounds;
};

#endif /* !SOUND_HPP_ */
