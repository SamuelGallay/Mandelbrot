#include "Option.h"

Option::Option(sf::RenderWindow &Window , Mandelbrot &Fractales):
mWindow(&Window),mMandelbrot(&Fractales),isRunning(true)
,mAddColor(200.f,150.f,*mWindow),mRed(*mWindow)
{
    mAddColor.setText("+Couleur");
    mAddColor.setPosition(400.f,250.f);

    mRed.setPosition(10.f,10.f);
}

void Option::run()
{
    isRunning = true;
    while(mWindow->isOpen() && isRunning)
    {
        processEvent();
        render();
    }
}

void Option::processEvent()
{
    sf::Event event;
    while(mWindow->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow->close();
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            isRunning = false;
    }
    mAddColor.Test();
    mRed.update(event);
}

void Option::render()
{
    mWindow->clear();
    mWindow->draw(mAddColor);
    mWindow->draw(mRed);
    mWindow->display();
}


