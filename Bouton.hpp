#ifndef BOUTON_HPP
#define BOUTON_HPP


class Bouton : public sf::Drawable, public sf::Transformable
{
    public:
        Bouton(int x,int y);

    protected:

    private:
        //virtual void draw();
        sf::Rect mForme;
};

#endif // BOUTON_HPP
