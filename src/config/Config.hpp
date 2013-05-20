#ifndef CONFIG_H
#define CONFIG_H

#include "util/JsonReader.hpp"

#include <cstdint>

namespace gol
{
    class config
    {
        util::JsonReader reader;

        std::uint32_t screen_width, screen_height, cell_width, cell_height, grid_width, grid_height, propagation_speed;
        std::string path_on, path_off;

    public:
        config(const std::string &path = "config.json") 
        : reader(path) 
        {
            screen_width      = reader.getProperty<std::uint32_t>("gol.settings.screen_width"     );
            screen_height     = reader.getProperty<std::uint32_t>("gol.settings.screen_height"    );
            cell_width        = reader.getProperty<std::uint32_t>("gol.settings.cell_width"       );
            cell_height       = reader.getProperty<std::uint32_t>("gol.settings.cell_height"      );
            grid_width        = reader.getProperty<std::uint32_t>("gol.settings.grid.width"       );
            grid_height       = reader.getProperty<std::uint32_t>("gol.settings.grid.height"      );
            propagation_speed = reader.getProperty<std::uint32_t>("gol.settings.propagation_speed");
            path_on           = reader.getProperty<std::string  >("gol.images.cell_on"            );
            path_off          = reader.getProperty<std::string  >("gol.images.cell_off"           );
        }
        config(config const &) = delete;
        config(config &&)      = delete;
        config &operator=(config const &) = delete;
        config &operator=(config &&)      = delete;

        ~config() { FreeInstance(); }

        static config *inst()
        {
            static config *instance = new config();
            return instance;
        }
        static void FreeInstance()
        {
            delete inst();
        }

        std::uint32_t getScreenWidth()      const { return screen_width;      }
        std::uint32_t getScreenHeight()     const { return screen_height;     }
        std::uint32_t getCellWidth()        const { return cell_width;        }
        std::uint32_t getCellHeight()       const { return cell_height;       }
        std::uint32_t getGridWidth()        const { return grid_width;        }
        std::uint32_t getGridHeight()       const { return grid_height;       }
        std::uint32_t getPropagationSpeed() const { return propagation_speed; }
        std::string   getPathOn()           const { return path_on;           }
        std::string   getPathOff()          const { return path_off;          }
    };
}

#endif