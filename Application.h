#ifndef MANDELBROT_APPLICATION_H
#define MANDELBROT_APPLICATION_H

#include <SFML/Graphics.hpp>

#include "Parameters.h"
#include "GUI.h"
#include <memory>

class Application {
public:
    Application();

    void run();

private:
    void wallpaper(Parameters c_param);

    void handleInputs(sf::Event event);

    void runWorker();

    sf::RenderWindow window;
    std::shared_ptr<sf::Image> rendu;
    double vitesse;
    double vitZoom;
    int flou;
    sf::Clock clock;

    Parameters param;
    GUI gui;
};

#endif //MANDELBROT_APPLICATION_H
