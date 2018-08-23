#include "Option.hpp"

#include <string>
#include <sstream>

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
    mRed.update(event);
    std::string colorStrRed = mRed.getText();
    std::stringstream strToInt (colorStrRed);
    int colorRed(0);
    strToInt >> colorRed;
    if(colorRed>255)
        mRed.write("255");

    mAddColor.Test();

}

void Option::render()
{
    mWindow->clear();
    mWindow->draw(mAddColor);
    mWindow->draw(mRed);
    mWindow->display();
}


