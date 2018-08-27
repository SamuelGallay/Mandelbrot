#include "Mandelbrot.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <iomanip>
#include <gmp.h>
#include <gmpxx.h>

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

    const std::string number = "3.141592653589793238462643383279502884197169399375105820974944592307816406286";
    mpf_class pi(number, 200);

    std::cout << std::setprecision(200) << pi << std::endl;
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

std::vector< std::complex<double> > Mandelbrot::basePoint(std::complex<double> c)
{
    std::vector< std::complex<double> > table;
    std::complex<double> z(0.0, 0.0);
    
    for(unsigned int i=0; i<iterMax; i++){
        table.push_back(z);
        z = z * z + c;
        if(std::norm(z) > 4)
            return table;
    }
    
    return table;
}

void Mandelbrot::update()
{
    std::cout << "Zoom : " << zoom << std::endl;
    std::cout << "IterMax : " << iterMax << std::endl;
    
    std::complex<double> start  ( (0.5 * vue.width/zoom + vue.left - vue.width/ zoom/2) ,
                            (0.5 * vue.height/zoom + vue.top - vue.height/ zoom/2) );
    std::vector< std::complex<double> > table = basePoint(start);
    std::cout << table.size() << "/" << iterMax << std::endl;
    
    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            std::complex<double> c ( (static_cast<double>(abscisse) / static_cast<double>(rendu.getSize().x)  * vue.width/zoom + vue.left - vue.width/ zoom/2) ,
                                   (static_cast<double>(ordonnee) / static_cast<double>(rendu.getSize().y) * vue.height/zoom + vue.top - vue.height/ zoom/2) );
            std::complex<double> d0 = c - start;
            std::complex<double> dn = d0;
            unsigned int i = 0;
            
            while (std::norm(dn + table[i]) < 1024 && i < table.size()) {
                dn = (table[i+1] + table[i+1])*dn + dn*dn + d0;
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
            
            int depart = (int) liste.size() - 1;
            int arrivee = 0;
            
            while (static_cast<float>(depart)/static_cast<float>(liste.size()-1) > distAbs) {depart--;}
            while (static_cast<float>(arrivee)/static_cast<float>(liste.size()-1) < distAbs) {arrivee++;}
            
            float distRel = ( distAbs - static_cast<float>(depart)/static_cast<float>(liste.size()-1) ) * (liste.size()-1);
            
            sf::Color couleur;
            if (i == iterMax)
                couleur = sf::Color::Black;
            else {
	      couleur.r = (int)( liste[depart].r + (liste[arrivee].r - liste[depart].r) * distRel );
	      couleur.g = (int)( liste[depart].g + (liste[arrivee].g - liste[depart].g) * distRel );
	      couleur.b = (int)( liste[depart].b + (liste[arrivee].b - liste[depart].b) * distRel );
            }
            rendu.setPixel(abscisse, ordonnee, couleur);
        }
    }
}
