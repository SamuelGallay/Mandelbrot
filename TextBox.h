#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "SFML/Graphics.hpp"
#include <string>

class TextBox : public sf::Drawable, public sf::Transformable
{
    public:
        TextBox(sf::RenderWindow &Window);
        sf::FloatRect getGlobalBounds();
        void update(sf::Event &event);
        void write(std::string Text);
        std::string getText();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RenderWindow* mWindow;
        sf::Font mFont;
        sf::Text mText;
        sf::RectangleShape mBox;
        bool isSelect;
        std::string mString;
};

#endif // TEXTBOX_H
