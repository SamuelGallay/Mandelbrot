#include "Bouton.hpp"

Bouton::Bouton(int x,int y):mForme(x,y,200.f,100.f)
{
    //ctor
}
/*
virtual void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        // on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
    states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

        // on applique la texture
    states.texture = &m_texture;

        // on peut aussi surcharger states.shader ou states.blendMode si nécessaire

        // on dessine le tableau de vertex
    target.draw(m_vertices, states);
}
*/
