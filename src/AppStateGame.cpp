#include "AppStateGame.hpp"
#include "core/TextureManager.hpp"
#include "config/Config.hpp"

namespace gol
{
    AppStateGame::AppStateGame(Application *_app, sf::RenderWindow *_display)
    : core::AppState(_display)
    , app(_app)
    , grid(config::inst()->getGridWidth(), config::inst()->getGridHeight())
    , cell_width(config::inst()->getCellWidth())
    , cell_height(config::inst()->getCellHeight())
    , screen_width(config::inst()->getScreenWidth())
    , screen_height(config::inst()->getScreenHeight())
    , speed(config::inst()->getPropagationSpeed())
    , running(false)
    {
        sf::Texture &temp = core::TextureManager::getInstance().Load(config::inst()->getPathOn());
        temp.setSmooth(true);
        cell_on = sf::Sprite(temp);

        sf::Texture &temp2 = core::TextureManager::getInstance().Load(config::inst()->getPathOff());
        temp2.setSmooth(true);
        cell_off = sf::Sprite(temp2);

        view = display->getDefaultView();
        view.setCenter((grid.getWidth()*cell_width)/2, (grid.getHeight()*cell_height)/2);
        display->setView(view);
    }

    int AppStateGame::id()
    {
        return 1;
    }

    void AppStateGame::OnRender()
    {
        if(running)
        {
            if(updateTimer.getElapsedTime().asMilliseconds() >= speed)
            {
                grid.update();
                updateTimer.restart();
            }
        }

        for(int i = 0; i != grid.getWidth(); ++i)
        {
            for(int j = 0; j != grid.getHeight(); ++j)
            {
                bool state = grid.getState(i, j);
                if(state)
                {
                    cell_on.setPosition(i*cell_width, j*cell_height);
                    display->draw(cell_on);
                }
                else
                {
                    cell_off.setPosition(i*cell_width, j*cell_height);
                    display->draw(cell_off);
                }
            }
        }
    }

    void AppStateGame::OnLButtonPressed(int x, int y) noexcept
    {
        sf::Vector2f worldPos = display->mapPixelToCoords(sf::Vector2i(x, y));
        grid.setState(worldPos.x/cell_width, worldPos.y/cell_height, true);
    }
    void AppStateGame::OnRButtonPressed(int x, int y) noexcept
    {
        sf::Vector2f worldPos = display->mapPixelToCoords(sf::Vector2i(x, y));
        grid.setState(worldPos.x/cell_width, worldPos.y/cell_height, false);
    }
    void AppStateGame::OnMouseMoved(int x, int y) noexcept
    {
        if(x >= screen_width || x < 0 || y >= screen_height || y < 0)
            return;

        sf::Vector2f worldPos = display->mapPixelToCoords(sf::Vector2i(x, y));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            grid.setState(worldPos.x/cell_width, worldPos.y/cell_height, true);
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            grid.setState(worldPos.x/cell_width, worldPos.y/cell_height, false);
    }
    void AppStateGame::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system) noexcept
    {
        if(key == sf::Keyboard::Key::Return)
            running = !running;
        else if(key == sf::Keyboard::Up)
        {
            speed -= 100;
            if(speed < 100)
                speed = 100;
        }
        else if(key == sf::Keyboard::Down)
        {
            speed += 100;
            if(speed > 1000)
                speed = 1000;
        }
    }
    void AppStateGame::OnMouseWheelMoved(int delta, int x, int y) noexcept
    {
        if(delta < 0)
            view.zoom(1.1f);
        else if(delta > 0)
            view.zoom(0.9f);
        display->setView(view);
    }
}