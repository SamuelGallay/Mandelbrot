#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Bouton.hpp"

class Menu
{
    public:
        Menu(sf::RenderWindow &appWindow);
        void run();
        bool getOk();

    private:
        void processEvents();
        void render();

    private:
        sf::RenderWindow *mWindow;
        bool isOk;
        Bouton mCommencer;
        Bouton mOption;

};

#endif // MENU_H
