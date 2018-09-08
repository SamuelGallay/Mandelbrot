#include "Option.hpp"

#include <string>
#include <sstream>

Option::Option(sf::RenderWindow &Window , Mandelbrot &Fractales):
mWindow(&Window),mMandelbrot(&Fractales),isRunning(true)
,mAddColor(200.f,100.f,*mWindow),mSupprColor(200.f,100.f,*mWindow),mRed(*mWindow),mGreen(*mWindow),mBlue(*mWindow),mListeCouleurs(mMandelbrot->getColors())
{
    mAddColor.setText("Ajouter couleur");
    mAddColor.setPosition(400.f,200.f);

    mSupprColor.setText("Supprimer Couleur");
    mSupprColor.setPosition(400.f,300.f);

    mRed.setPosition(100.f,100.f);
    mGreen.setPosition(100.f,200.f);
    mBlue.setPosition(100.f,300.f);
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
        mRed.update(event);
        mGreen.update(event);
        mBlue.update(event);
    }


    if(stringToInt(mRed.getText())>255)
        mRed.write("255");
    if(stringToInt(mGreen.getText())>255)
        mGreen.write("255");
    if(stringToInt(mBlue.getText())>255)
        mBlue.write("255");

    if(mAddColor.Test())
    {
        sf::Color newColor(stringToInt(mRed.getText()),stringToInt(mGreen.getText()),stringToInt(mBlue.getText()));
        mListeCouleurs.push_back(newColor);
    }
    if(mSupprColor.Test()&&mListeCouleurs.size()>=0)
    {
        mListeCouleurs.pop_back();
    }


}

void Option::render()
{
    mWindow->clear();
    mWindow->draw(mAddColor);
    mWindow->draw(mSupprColor);

    for(unsigned int i(0);i<mListeCouleurs.size();i++)
    {
        sf::RectangleShape rColor(sf::Vector2f(50,50));
        rColor.setPosition(900,(i*51)+5);
        rColor.setFillColor(mListeCouleurs[i]);
        mWindow->draw(rColor);
    }

    mWindow->draw(mRed);
    mWindow->draw(mGreen);
    mWindow->draw(mBlue);
    mWindow->display();
}

int Option::stringToInt(std::string theString)
{
    std::stringstream strToInt (theString);
    int theInt(0);
    strToInt >> theInt;

    return theInt;
}
