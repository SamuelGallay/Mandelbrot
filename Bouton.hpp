#ifndef BOUTON_HPP
#define BOUTON_HPP

#include <SFML/Graphics.hpp>

class Bouton : public sf::Drawable, public sf::Transformable
{
    public:
        Bouton(float x,float y);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape mForme;
};

#endif // BOUTON_HPP
