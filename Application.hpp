#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include "Mandelbrot.hpp"

class Application
{
public:
    Application();
    void run();
    
private:
    void processEvents();
    void render();
    
private:
    sf::RenderWindow mWindow;
    Mandelbrot mFractale;
    double mVitesse;
    double mVitZoom;
    int mFlou;
};

#endif
