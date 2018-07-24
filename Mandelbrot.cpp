#include "Mandelbrot.hpp"

Mandelbrot::Mandelbrot()
{
    iterMax = 50;
    vue = sf::Rect<float>(-0.75, 0, 2.7, 2.4);
    zoom = 1.0;
}

Mandelbrot::Mandelbrot(unsigned int width, unsigned int height)
{
    iterMax = 50;
    vue = sf::Rect<float>(-0.75, 0, 2.7, 2.4);
    zoom = 1.0;
    setSize(width, height);
}

void Mandelbrot::setSize(unsigned int width, unsigned int height)
{
    if ( (rendu.getSize().x != width) || (rendu.getSize().y != height) )
    {
        rendu.create(width, height, sf::Color::Black);
        iterations.resize(width * height);
        if (static_cast<float>(width) / static_cast<float>(height) >= 1.0){
            vue.width = 2.7 * static_cast<float>(width) / static_cast<float>(height);
            vue.height = 2.4;
        }
        else{
            vue.width = 2.7;
            vue.height = 2.4 * static_cast<float>(height) / static_cast<float>(width);
        }
        update();
    }
}

void Mandelbrot::update()
{
    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            std::complex<float> c ( (static_cast<float>(abscisse) / static_cast<float>(rendu.getSize().x)  * vue.width/zoom + vue.left - vue.width/ zoom/2) ,
                                   (static_cast<float>(ordonnee) / static_cast<float>(rendu.getSize().y) * vue.height/zoom + vue.top - vue.height/ zoom/2) );
            std::complex<float> z(0.0, 0.0);
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
    for (unsigned int abscisse = 0; abscisse < rendu.getSize().x; abscisse++)
    {
        for (unsigned int ordonnee = 0; ordonnee < rendu.getSize().y; ordonnee++)
        {
            unsigned int i = iterations[abscisse * rendu.getSize().y + ordonnee];
            if (i == iterMax)
                rendu.setPixel(abscisse, ordonnee, sf::Color::Black);
            else
                rendu.setPixel(abscisse, ordonnee, sf::Color((i*100/iterMax), (i*215/iterMax), (i*255/iterMax) ) );
        }
    }
}
