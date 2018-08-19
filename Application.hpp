#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include "Mandelbrot.hpp"
#include "Menu.hpp"

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
    Menu mMenu;
    float mVitesse;
    float mVitZoom;
    int mFlou;
};

#endif
