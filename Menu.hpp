#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu
{
    public:
        Menu();
        void run();

    private:
        void processEvents();
        void render();

    private:
        sf::RenderWindow mWindow;
};

#endif // MENU_H
