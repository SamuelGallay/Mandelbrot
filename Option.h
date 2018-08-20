#ifndef OPTION_HPP
#define OPTION_HPP
#include "SFML/Graphics.hpp"
#include "Bouton.hpp"
#include "Mandelbrot.hpp"

class Option
{
    public:
        Option(sf::RenderWindow &Window , Mandelbrot &Fractales);
        void run();

    private:
        void processEvent();
        void render();

    private:
        sf::RenderWindow* mWindow;
        Mandelbrot* mMandelbrot;
        bool isRunning;
        Bouton mAddColor;

};

#endif // OPTION_HPP
