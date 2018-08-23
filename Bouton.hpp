#ifndef BOUTON_HPP
#define BOUTON_HPP

#include <SFML/Graphics.hpp>

#include <string>

class Bouton : public sf::Drawable, public sf::Transformable
{
    public:
        Bouton(float x,float y,sf::RenderWindow &window);
        sf::FloatRect getGlobalBounds();
        bool Test();
        void setText(std::string texteDuBouton);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape mForme;
        sf::Text mText;
        sf::Font mFont;
        bool isPressed;
        sf::RenderWindow *mWindow;
};

#endif // BOUTON_HPP
