#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu
{
    public:
        Menu();
        run();
        
    private:
        processEvents();
        render();

    private:
        sf::RenderWindow mWindow;
};

#endif // MENU_H
