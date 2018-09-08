#include "Option.hpp"

#include <string>
#include <sstream>

Option::Option(sf::RenderWindow &Window , Mandelbrot &Fractales):
mWindow(&Window),mMandelbrot(&Fractales),isRunning(true)
,mAddColor(200.f,150.f,*mWindow),mRed(*mWindow),mListeCouleurs(mMandelbrot->getColors())
{
    mAddColor.setText("AddThisColor");
    mAddColor.setPosition(400.f,250.f);

    mRed.setPosition(100.f,200.f);
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

    if(stringToInt(mRed.getText())>255)
        mRed.write("255");

    mAddColor.Test();

}

void Option::render()
{
    mWindow->clear();
    mWindow->draw(mAddColor);

    for(unsigned int i(0);i<mListeCouleurs.size();i++)
    {
        sf::RectangleShape rColor(sf::Vector2f(50,50));
        rColor.setPosition(900,(i*51)+5);
        rColor.setFillColor(mListeCouleurs[i]);
        mWindow->draw(rColor);
    }

    mWindow->draw(mRed);
    mWindow->display();
}

int Option::stringToInt(std::string theString)
{
    std::stringstream strToInt (theString);
    int theInt(0);
    strToInt >> theInt;

    return theInt;
}
