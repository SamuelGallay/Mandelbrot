#ifndef BOUTON_HPP
#define BOUTON_HPP

#include <SFML/Graphics.hpp>

class Bouton : public sf::Drawable, public sf::Transformable
{
    public:
        Bouton(float x,float y,sf::Window &window);
        sf::FloatRect getGlobalBounds();
        bool Test();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape mForme;
        sf::Text mText;
        int mSteps;
        sf::Window *mWindow;
};

#endif // BOUTON_HPP
