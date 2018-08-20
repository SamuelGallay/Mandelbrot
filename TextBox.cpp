#include "TextBox.h"

TextBox::TextBox(sf::RenderWindow &Window):mWindow(&Window),mBox(sf::Vector2f(50.f,12.f)),isSelect(false)
{
    if(!mFont.loadFromFile("police.ttf"))
    {}

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

void TextBox::update()
{
    sf::Vector2f mousePosition(sf::Mouse::getPosition(*mWindow));
    mousePosition-=getPosition();
    sf::FloatRect colisionBox(getGlobalBounds());
    if(colisionBox.contains(mousePosition))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelect = true;
            mBox.setFillColor(sf::Color::White);
        }
        if(!isSelect)
        {
            mBox.setFillColor(sf::Color(100,100,100));
        }

    }
    else
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelect = false;
            mBox.setFillColor(sf::Color(50,50,50));
        }
    }

    if(isSelect)
    {
        write();
    }

}

void TextBox::write()
{
    sf::Event event;
    while(mWindow->pollEvent(event))
    {
        if(event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode >47 && event.text.unicode <57)
            {
                mText.setString(event.text.unicode);
            }
        }
    }

}

//48//57
