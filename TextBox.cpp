#include "TextBox.hpp"

#include <iostream>



#if PHIL
#else
#include "police.hpp"
#endif // PHIL

TextBox::TextBox(sf::RenderWindow &Window):mWindow(&Window),mBox(sf::Vector2f(50.f,15.f)),isSelect(false),mString("")
{
    #if PHIL
    if(!mFont.loadFromFile("police.ttf"))
    {
        std::cout<<"impossible de charger la police de texte";
    }
    #else
    if(!mFont.loadFromMemory( policeData, sizeof(policeData) ))
    {
        std::cout<<"impossible de charger la police de texte";
    }
    #endif // PHIL
    mText.setFont(mFont);
    mText.setCharacterSize(10);
    mText.setFillColor(sf::Color::White);

    mBox.setFillColor(sf::Color::Black);
    mBox.setOutlineColor(sf::Color(50,50,50));
    mBox.setOutlineThickness(1);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mBox,states);
    target.draw(mText,states);
}

sf::FloatRect TextBox::getGlobalBounds()
{
    return mBox.getGlobalBounds();
}

void TextBox::update(sf::Event &event)
{
    sf::Vector2f mousePosition(sf::Mouse::getPosition(*mWindow));
    mousePosition-=getPosition();
    sf::FloatRect colisionBox(getGlobalBounds());
    if(colisionBox.contains(mousePosition))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelect = true;
            mBox.setOutlineColor(sf::Color::White);
        }
        if(!isSelect)
        {
            mBox.setOutlineColor(sf::Color(100,100,100));
        }

    }
    else
    {
        if(isSelect && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelect = false;
            mBox.setOutlineColor(sf::Color(50,50,50));
        }
        if(!isSelect)
        {
            mBox.setOutlineColor(sf::Color(50,50,50));
        }
    }
    if(isSelect)
    {
        if(event.text.unicode>47 && event.text.unicode<58)
        {
            char number (event.text.unicode);
            if(mString.size()<3)
            {
                mString+=number;
                write(mString);
            }
        }
        //problème dans cette condition
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
        {
            if(mString.size()>0)
            {
                mString.pop_back();
            }
        }
    }
}

void TextBox::write(std::string Text)
{
    mText.setString(Text);
    sf::FloatRect textSize(mText.getGlobalBounds());
    mText.setPosition(sf::Vector2f (( mBox.getSize().x - textSize.width )/2 , ( mBox.getSize().y - textSize.height )/2));
}

std::string TextBox::getText()
{
    return mString;
}
