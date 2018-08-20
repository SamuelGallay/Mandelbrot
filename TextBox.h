#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include "SFML/Graphics.hpp"

class TextBox : public sf::Drawable, public sf::Transformable
{
    public:
        TextBox(sf::RenderWindow &Window);
        sf::FloatRect getGlobalBounds();
        void update();
        void write();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RenderWindow* mWindow;
        sf::Font mFont;
        sf::Text mText;
        sf::RectangleShape mBox;
        bool isSelect;
};

#endif // TEXTBOX_H
