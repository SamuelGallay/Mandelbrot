#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &appWindow):mWindow(&appWindow),mCommencer(200.f,100.f,*mWindow),isOk(false)
{
    mWindow->setFramerateLimit(30);
    mCommencer.setPosition(400.f,250.f);
    mCommencer.setText("Commencer");
}

void Menu::run()
{
    while(mWindow->isOpen()&&!isOk)
    {
        processEvents();
        render();
    }

}

void Menu::processEvents()
{
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow->close();
    }
    if(mCommencer.Test())
    {
        isOk=true;
        //mWindow->close();
    }
}

void Menu::render()
{
    mWindow->clear(sf::Color(21,21,21));
    mWindow->draw(mCommencer);
    mWindow->display();
}

bool Menu::getOk()
{
    return isOk;
}
