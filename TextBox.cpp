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
            mBox.setOutlineColor(sf::Color::White);
        }
        if(!isSelect)
        {
            mBox.setOutlineColor(sf::Color(100,100,100));
        }

    }
    else
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelect = false;
            mBox.setOutlineColor(sf::Color(50,50,50));
        }
    }

    if(isSelect)
    {
        write("Hhi");
    }

}

void TextBox::write(std::string Text)
{
    mText.setString(Text);
    sf::FloatRect textSize(mText.getGlobalBounds());
    mText.setPosition(sf::Vector2f (( mBox.getSize().x - textSize.width )/2 , ( mBox.getSize().y - textSize.height )/2));
}

//48//57
