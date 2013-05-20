#include "Grid.hpp"
#include "core/Exception.hpp"
#include <iostream>

namespace gol { namespace logic
{

    Grid::Grid(const std::uint32_t &width, const std::uint32_t &height, const bool &state)
    : grid(width*height, Cell(state))
    , w(width)
    , h(height)
    {
    }

    void Grid::setState(const int &x, const int &y, const bool &state) 
    {
        if(x > w || x < 0 || y > h || y < 0)
            throw core::exception("Grid::setState parameter out of bounds.");
        grid[x+y*w].setState(state);
    }
    void Grid::toggleState(const int &x, const int &y) 
    {
        if(x > w || x < 0 || y > h || y < 0)
            throw core::exception("Grid::toggleState parameter out of bounds.");
        grid[x+y*w].toggle();
    }
    bool Grid::getState(const int &x, const int &y) const 
    {
        if(x >= w || x < 0 || y >= h || y < 0)
        {
            std::clog << "The state of a cell out of bounds at (" << x << ", " << y << ") was requested." << std::endl;
            return false;
        }
        return grid[x+y*w];
    }

    int Grid::numLivingNeighbors(const int &x, const int &y)
    {
        int ret = 0;
        if(getState(x-1, y))
            ++ret;
        if(getState(x-1, y-1))
            ++ret;
        if(getState(x, y-1))
            ++ret;
        if(getState(x+1, y-1))
            ++ret;
        if(getState(x+1, y))
            ++ret;
        if(getState(x+1, y+1))
            ++ret;
        if(getState(x, y+1))
            ++ret;
        if(getState(x-1, y+1))
            ++ret;

        return ret;
    }

    std::uint32_t Grid::getWidth()  const { return w; }
    std::uint32_t Grid::getHeight() const { return h; }

    void Grid::update()
    {
        for(int x = 0; x < w; ++x)
        {
            for(int y = 0; y < h; ++y)
            {
                int livingNeighbors = numLivingNeighbors(x, y);
                Cell &current = grid.at(x+y*w);
                if(current)
                {
                    if(livingNeighbors < 2 || livingNeighbors > 3)
                        current.toggle();
                }
                else
                {
                    if(livingNeighbors == 3)
                        current.toggle();
                }
            }
        }
        for(auto &i: grid)
            i.update();
    }
}}