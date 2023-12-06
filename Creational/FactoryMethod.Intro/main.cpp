#include "factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>

namespace StronglyCoupled
{
    class MusicApp
    {
    public:
        MusicApp() = default;

        void play(const std::string& track_title)
        {
            // creation of product
            SpotifyService music_service("spotify_user", "rjdaslf276%2", 45);

            std::optional<Track> track = music_service.get_track(track_title);

            // using of product
            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto& note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

class MusicApp
{
    MusicServiceCreator music_service_creator_;

public:
    MusicApp(MusicServiceCreator music_service_creator)
        : music_service_creator_(music_service_creator)
    {
    }

    void play(const std::string& track_title)
    {
        // creation of the object
        std::unique_ptr<MusicService> music_service = music_service_creator_();

        // usage of the object
        std::optional<Track> track = music_service->get_track(track_title);

        if (track)
        {
            std::cout << "Playing track: ";
            for (const auto& note : *track)
                std::cout << note << ".";
            std::cout << "|\n";
        }
        else
        {
            std::cout << "Track not found!\n";
        }
    }
};

namespace StaticFactory
{
    std::unique_ptr<MusicService> create_music_service(const std::string& id)
    {
        if (id == "Tidal")
            return std::make_unique<TidalService>("tidal_user", "KJH8324d&df");
        else if (id == "Spotify")
            return std::make_unique<SpotifyService>("spotify_user", "rjdaslf276%2", 45);

        throw std::invalid_argument("ID not supported");
    }   
}

// parametrized factory
using MusicServiceFactory = std::unordered_map<std::string, MusicServiceCreator>;

void most_common_used_factory_method()
{
    std::vector<int> vec = {1, 2, 3};

    for(auto it = std::ranges::begin(vec); it != std::ranges::end(vec); ++it) // vec.begin() & vec.end() - factory methods
        std::cout << *it << " ";
    std::cout << "\n";
}

int main()
{
    MusicServiceFactory music_service_factory;
    music_service_factory.emplace("Tidal", TidalServiceCreator("tidal_user", "KJH8324d&df"));
    music_service_factory.emplace("Spotify", SpotifyServiceCreator("spotify_user", "rjdaslf276%2", 45));
    music_service_factory.emplace("Filesystem", []{ return std::make_unique<FilesystemMusicService>("/music"); });

    std::string id_from_config = "Tidal";
    MusicApp app(music_service_factory.at(id_from_config));
    app.play("Would?");
}