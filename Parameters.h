#ifndef MANDELBROT_PARAMETERS_H
#define MANDELBROT_PARAMETERS_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Parameters {
    std::vector<sf::Color> liste;
    sf::Vector2<unsigned int> definition;
    unsigned int iterMax;
    sf::Vector2<double> center;
    double zoom;

    bool operator==(Parameters &a) {
        if (liste == a.liste &&
            definition == a.definition &&
            iterMax == a.iterMax &&
            center == a.center &&
            zoom == a.zoom)
            return true;
        else
            return false;
    }

    bool operator!=(Parameters &a) {
        return !(*this == a);
    }

    Parameters() {
        liste.push_back(sf::Color::Black);
        liste.push_back(sf::Color::Blue);
        liste.push_back(sf::Color::Yellow);
        liste.push_back(sf::Color::Magenta);
        liste.push_back(sf::Color::Red);
        liste.push_back(sf::Color::Yellow);
        liste.push_back(sf::Color::Magenta);
        liste.push_back(sf::Color::Red);

        definition = sf::Vector2<unsigned int>(1000, 600);
        iterMax = 50;
        center = sf::Vector2<double>(-0.75, 0.0);
        zoom = 1.0;

    }
};

#endif //MANDELBROT_PARAMETERS_H
