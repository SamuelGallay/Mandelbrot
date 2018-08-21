#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Bouton.hpp"
#include "police.hpp"

Bouton::Bouton(float x,float y,sf::RenderWindow &window):mForme(sf::Vector2f(x,y)),isPressed(false),mWindow(&window)
{
    mForme.setFillColor(sf::Color(50,50,150));
    mForme.setOutlineColor(sf::Color::Black);
    mForme.setOutlineThickness(1.f);

    if(!mFont.loadFromMemory( policeData, sizeof(policeData) ))
    {
        std::cout<<"impossible de charger la police de texte";
    }

    mText.setFont(mFont);
    mText.setString("");
    mText.setFillColor(sf::Color::White);
    mText.setCharacterSize(20);
}

void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mForme,states);
    target.draw(mText,states);
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
            isPressed = true;
            mForme.setFillColor(sf::Color(75,75,150));
        }

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)&& !isPressed)
        {
            mForme.setFillColor(sf::Color(100,100,150));
        }

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)&& isPressed)
        {
            mForme.setFillColor(sf::Color(75,75,150));
            isPressed = false;
            return true;
        }

    }
    else
    {
        mForme.setFillColor(sf::Color(0,0,255));
        isPressed = false;
    }
    return false;
}

void Bouton::setText(std::string texteDuBouton)
{
    mText.setString(texteDuBouton);
    sf::FloatRect textSize(mText.getGlobalBounds());

    mText.setPosition(sf::Vector2f (( mForme.getSize().x - textSize.width )/2 , ( mForme.getSize().y - textSize.height )/2));
}
