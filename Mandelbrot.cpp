#include "Mandelbrot.hpp"

#include <cassert>
#include <iostream>
#include <complex>
#include <cmath>

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height)
{
    iterMax = 50;
    vue = sf::Rect<double>(-0.75, 0, 2.7, 2.4);
    zoom = 1.0;
    liste.push_back(sf::Color::Black);
    liste.push_back(sf::Color::Blue);
    liste.push_back(sf::Color::Yellow);
    liste.push_back(sf::Color::Magenta);
    liste.push_back(sf::Color::Red);
    liste.push_back(sf::Color::Yellow);
    liste.push_back(sf::Color::Magenta);
    liste.push_back(sf::Color::Red);

    setSize(width, height);
}

void Mandelbrot::setSize(unsigned int width, unsigned int height)
{
    if ( (rendu.getSize().x != width) || (rendu.getSize().y != height) )
    {
        rendu.create(width, height, sf::Color::Black);
        iterations.resize(width * height);
        if (static_cast<double>(width) / static_cast<double>(height) >= 1.0){
            vue.width = 2.7 * static_cast<double>(width) / static_cast<double>(height);
            vue.height = 2.4;
        }
        else{
            vue.width = 2.7;
            vue.height = 2.4 * static_cast<double>(height) / static_cast<double>(width);
        }
        update();
    }
}

void Mandelbrot::update()
{
    std::cout << "Zoom : " << zoom << std::endl;
    std::cout << "IterMax : " << iterMax << std::endl;
    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            std::complex<double> c ( (static_cast<double>(abscisse) / static_cast<double>(rendu.getSize().x)  * vue.width/zoom + vue.left - vue.width/ zoom/2) ,
                                   (static_cast<double>(ordonnee) / static_cast<double>(rendu.getSize().y) * vue.height/zoom + vue.top - vue.height/ zoom/2) );
            std::complex<double> z(0.0, 0.0);
            unsigned int i = 0;

            while (std::norm(z) < 4 && i < iterMax) {
                z = z * z + c;
                i++;
            }
            iterations[abscisse * rendu.getSize().y + ordonnee] = i;
        }
    }
    render();
}

void Mandelbrot::render(){
    assert(liste.size() >= 2);

    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            unsigned int i = iterations[abscisse * rendu.getSize().y + ordonnee];
            float distAbs = static_cast<float>(i)/static_cast<float>(iterMax);

            int depart = liste.size() - 1;
            int arrivee = 0;

            while (static_cast<float>(depart)/static_cast<float>(liste.size()-1) > distAbs) {depart--;}
            while (static_cast<float>(arrivee)/static_cast<float>(liste.size()-1) < distAbs) {arrivee++;}

            float distRel = ( distAbs - static_cast<float>(depart)/static_cast<float>(liste.size()-1) ) * (liste.size()-1);

            sf::Color couleur;
            if (i == iterMax)
                couleur = sf::Color::Black;
            else {
                couleur.r = liste[depart].r + static_cast<sf::Uint8>( (liste[arrivee].r - liste[depart].r) * distRel );
                couleur.g = liste[depart].g + static_cast<sf::Uint8>( (liste[arrivee].g - liste[depart].g) * distRel );
                couleur.b = liste[depart].b + static_cast<sf::Uint8>( (liste[arrivee].b - liste[depart].b) * distRel );
            }
            rendu.setPixel(abscisse, ordonnee, couleur);
        }
    }
}

void Mandelbrot::move(sf::Vector2f direction){
    vue.left += direction.x / zoom;
    vue.top += direction.y / zoom;
    update();
}

void Mandelbrot::setZoom(double ratio){
    zoom = ratio;
    iterMax = static_cast<unsigned int>(100*std::log(ratio+1));
    update();
}

void Mandelbrot::setColors(std::vector<sf::Color> newList){
	liste = newList;
	render();
}
