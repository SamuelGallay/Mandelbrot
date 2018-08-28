#include "Mandelbrot.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <gmp.h>
#include <gmpxx.h>

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height)
{
    iterMax = 69;
    
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


void Mandelbrot::update()
{
    x.real(0.5/zoom*(vue.width-vue.width) + vue.left);
    x.imag(0.5/zoom*(vue.height-vue.height) + vue.top);
    basePoint();
    
    std::cout << "Zoom : " << zoom << std::endl;
    std::cout << "IterMax : " << xn.size() << "/" << iterMax << std::endl;
    
    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            std::complex<double> c ( (static_cast<double>(abscisse) / static_cast<double>(rendu.getSize().x)  * vue.width/zoom + vue.left - vue.width/ zoom/2) ,
                                    (static_cast<double>(ordonnee) / static_cast<double>(rendu.getSize().y) * vue.height/zoom + vue.top - vue.height/ zoom/2) );
            unsigned int i = 0;
            if( (c.real()+1)*(c.real()+1) + c.imag()*c.imag() < 0.0625 or c.real() < sqrt((c.real()-0.25)*(c.real()-0.25) + c.imag()*c.imag()) - 2*((c.real()-0.25)*(c.real()-0.25) + c.imag()*c.imag()) + 0.25){
                i = xn.size();
                if(!optimal){
                    x = c;
                    basePoint();
                    optimal = true;
                }
            }
            else{
                std::complex<double> d0 = c - x;
                std::complex<double> dn = d0;
                do
                {
                    dn *= (xn[i+1] + xn[i+1]) + dn;
                    dn += d0;
                    ++i;
                }
                while (std::norm(xn[i+1] + dn) < 10000 && i < xn.size());
                if(i == xn.size()-1 && !optimal)
                {
                    x = c;
                    basePoint();
                    if(xn.size() == iterMax)
                        optimal = true;
                }
            }
            iterations[abscisse * rendu.getSize().y + ordonnee] = i;
        }
    }
    render();
}

void Mandelbrot::basePoint()
{
    mpf_set_default_prec(2048);
    xn.clear();
    optimal = false;
    mpf_class zr = 0;
    mpf_class zi = 0;
    mpf_class cr = x.real();
    mpf_class ci = x.imag();
    for(unsigned int i=0; i<iterMax; i++)
    {
        std::complex<double> z(zr.get_d(), zi.get_d());
        xn.push_back(z);
        mpf_class zr_temp = zr + zr;
        zr = zr * zr - zi * zi + cr;
        zi = zr_temp * zi + ci;
        if(std::norm(z) > 1000000)
            return;
    }
    optimal = true;
    return;
}

void Mandelbrot::render(){
    assert(liste.size() >= 2);
    
    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            unsigned int i = iterations[abscisse * rendu.getSize().y + ordonnee];
            float distAbs = static_cast<float>(i)/static_cast<float>(xn.size());
            
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
