#ifndef _APPSTATEGAME_H
#define _APPSTATEGAME_H

#include "core/AppState.hpp"
#include "core/SFML.hpp"
#include "logic/Grid.hpp"

#include <iostream>

namespace gol
{
    class Application;
    class AppStateGame : public core::AppState
    {
        Application *app;
        sf::Sprite cell_on, cell_off;
        sf::Clock updateTimer;
        sf::View view;

        logic::Grid grid;

        int cell_width, cell_height, screen_width, screen_height, speed;
        bool running;

    public:
        AppStateGame(Application *_app, sf::RenderWindow *_display);
        virtual ~AppStateGame()
        {
        }

        virtual int id();
        virtual void OnRender();

        virtual void OnLButtonPressed(int x, int y) noexcept;
        virtual void OnRButtonPressed(int x, int y) noexcept;
        virtual void OnMouseMoved(int x, int y) noexcept;
        virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) noexcept;
        virtual void OnMouseWheelMoved(int delta, int x, int y) noexcept;
    };
}

#endif