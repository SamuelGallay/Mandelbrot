#ifndef OPTION_HPP
#define OPTION_HPP

#include <SFML/Graphics.hpp>

#include "Bouton.hpp"
#include "Mandelbrot.hpp"
#include "TextBox.hpp"

class Option
{
    public:
        Option(sf::RenderWindow &Window , Mandelbrot &Fractales);
        void run();

    private:
        void processEvent();
        void render();
        int stringToInt(std::string theString);

    private:
        sf::RenderWindow* mWindow;
        Mandelbrot* mMandelbrot;
        bool isRunning;
        Bouton mAddColor;
        Bouton mSupprColor;
        TextBox mRed;
        TextBox mGreen;
        TextBox mBlue;
        std::vector<sf::Color> mListeCouleurs;
};

#endif // OPTION_HPP
