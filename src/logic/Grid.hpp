#ifndef GAMEOFLIFEGRID_H
#define GAMEOFLIFEGRID_H

#include "Cell.hpp"
#include <vector>
#include <cstdint>

namespace gol { namespace logic
{

    class Grid
    {
        std::vector<Cell> grid;
        std::uint32_t w, h;

    public:
        Grid() = delete;
        Grid(const std::uint32_t &width, const std::uint32_t &height, const bool &state = false);

        void setState   (const int &x, const int &y, const bool &state);
        void toggleState(const int &x, const int &y);
        bool getState   (const int &x, const int &y) const;

        std::uint32_t getWidth()  const;
        std::uint32_t getHeight() const;

        int  numLivingNeighbors(const int &x, const int &y);
        void update();
    };

}}

#endif