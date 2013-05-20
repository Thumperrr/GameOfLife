#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "core/AppState.hpp"
#include "core/SFML.hpp"
#include "AppStateGame.hpp"

namespace gol
{
    class Application
    {
        sf::RenderWindow display;
        bool running;
        core::AppState *state;
        void OnEvent(sf::Event *Event);

    public:
        Application();
        ~Application();

        template<class NewState>
        void ChangeState()
        {
            delete state;
            state = new NewState;
        }
        int Exec();
    };
}

#endif