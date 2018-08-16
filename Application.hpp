#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include "Mandelbrot.hpp"

class Application
{
public:
    Application(sf::RenderWindow &appWindow);
    void run();

private:
    void processEvents();
    void render();

private:
    sf::RenderWindow *mWindow;
    Mandelbrot mFractale;
    float mVitesse;
    float mVitZoom;
    int mFlou;
};

#endif
