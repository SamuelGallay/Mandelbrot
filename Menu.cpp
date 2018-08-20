#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &appWindow , Option &MenuOption):mWindow(&appWindow),mMenuOption(&MenuOption),isOk(false)
,mCommencer(200.f,100.f,*mWindow)
,mOption(200.f,100.f,*mWindow)
{
    mCommencer.setPosition(400.f,250.f);
    mCommencer.setText("Commencer");

    mOption.setPosition(400.f,400.f);
    mOption.setText("Option");
}

void Menu::run()
{
    isOk=false;
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
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            mWindow->close();
    }
    if(mCommencer.Test())
        isOk=true;
    if(mOption.Test())
        mMenuOption->run();

}

void Menu::render()
{
    mWindow->clear(sf::Color(21,21,21));
    mWindow->draw(mCommencer);
    mWindow->draw(mOption);
    mWindow->display();
}

bool Menu::getOk()
{
    return isOk;
}
