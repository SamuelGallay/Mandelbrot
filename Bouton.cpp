#include "Bouton.hpp"

Bouton::Bouton(int x,int y):mForme(x,y,200.f,100.f)
{
    //ctor
}
/*
virtual void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        // on applique la transformation de l'entit� -- on la combine avec celle qui a �t� pass�e par l'appelant
    states.transform *= getTransform(); // getTransform() est d�finie par sf::Transformable

        // on applique la texture
    states.texture = &m_texture;

        // on peut aussi surcharger states.shader ou states.blendMode si n�cessaire

        // on dessine le tableau de vertex
    target.draw(m_vertices, states);
}
*/
