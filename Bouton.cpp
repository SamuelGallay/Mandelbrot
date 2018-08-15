#include "Bouton.hpp"
#include "iostream"
#include <SFML/Graphics.hpp>

Bouton::Bouton(float x,float y,sf::Window &window):mForme(sf::Vector2f(x,y)),mSteps(0),mWindow(&window)
{
    mForme.setFillColor(sf::Color(50,50,150));
}

void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
    states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

    // on applique la texture
    //states.texture = &m_texture;

    // on peut aussi surcharger states.shader ou states.blendMode si nécessaire

    // on dessine le tableau de vertex
    //target.draw(m_vertices, states);
    target.draw(mForme,states);
}

sf::FloatRect Bouton::getGlobalBounds()
{
    return mForme.getGlobalBounds();
}

bool Bouton::Test()
{
    sf::Vector2f mousePosition(sf::Mouse::getPosition(*mWindow));
    sf::FloatRect colisionBox(mForme.getGlobalBounds());
    if(colisionBox.contains(mousePosition))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mSteps=1;
            mForme.setFillColor(sf::Color(255,000,000));
        }

        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)&& mSteps == 0)
        {
            mForme.setFillColor(sf::Color(000,255,000));
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


