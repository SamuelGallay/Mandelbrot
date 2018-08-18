#include "Bouton.hpp"
#include "iostream"
#include <SFML/Graphics.hpp>
#include <string>

Bouton::Bouton(float x,float y,sf::RenderWindow &window):mForme(sf::Vector2f(x,y)),mSteps(0),mWindow(&window)
{
    mForme.setFillColor(sf::Color(50,50,150));
    mForme.setOutlineColor(sf::Color::Black);
    mForme.setOutlineThickness(1.f);

    sf::Font font;
    if(!font.loadFromFile("police.ttf"))
    {
        std::cout<<"impossible de charger la police de texte";
    }
    //impossible de draw le texte
    mText.setPosition(x,y);
    mText.setFont(font);
    mText.setString("nothing");
    mText.setFillColor(sf::Color::White);
    mText.setCharacterSize(10);
}

void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    states.transform *= getTransform();
    target.draw(mForme,states);


}

sf::FloatRect Bouton::getGlobalBounds()
{
    return mForme.getGlobalBounds();
}

bool Bouton::Test()
{
    sf::Vector2f mousePosition(sf::Mouse::getPosition(*mWindow));
    mousePosition-=getPosition();
    sf::FloatRect colisionBox(getGlobalBounds());
    if(colisionBox.contains(mousePosition))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mSteps=1;
            mForme.setFillColor(sf::Color(255,0,0));
        }

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)&& mSteps == 0)
        {
            mForme.setFillColor(sf::Color(0,255,0));
        }

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)&& mSteps == 1)
        {
            return true;
        }

    }
    else
    {
        mForme.setFillColor(sf::Color(0,0,255));
        mSteps=0;
    }
    return false;
}

void Bouton::setText(std::string texteDuBouton)
{
    mText.setString(texteDuBouton);
}
