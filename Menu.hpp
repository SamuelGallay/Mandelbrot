#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include "Bouton.hpp"
#include "Option.hpp"

class Menu
{
    public:
        Menu(sf::RenderWindow &appWindow, Option &MenuOption);
        void run();
        bool getOk();

    private:
        void processEvents();
        void render();

    private:
        sf::RenderWindow *mWindow;
        Option *mMenuOption;
        bool isOk;
        Bouton mCommencer;
        Bouton mOption;
};

#endif // MENU_HPP
