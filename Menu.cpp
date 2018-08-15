#include "Menu.hpp"

Menu::Menu():mWindow(sf::VideoMode(1000.f, 600.f), "Fractales"),mCommencer(50.f,50.f)
{
    mWindow.setFramerateLimit(30);
    mCommencer.setPosition(450.f,250.f);
}

void Menu::run()
{
    while(mWindow.isOpen())
    {
        processEvents();
        render();
    }

}

void Menu::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }

}

void Menu::render()
{
    mWindow.clear(sf::Color(21,21,21));
    mWindow.draw(mCommencer);
    mWindow.display();
}
