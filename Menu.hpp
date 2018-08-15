#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Bouton.hpp"

class Menu
{
    public:
        Menu();
        void run();
        bool getOk();

    private:
        void processEvents();
        void render();

    private:
        sf::RenderWindow mWindow;
        Bouton mCommencer;
        bool isOk;
};

#endif // MENU_H
