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

};

#endif //MANDELBROT_PARAMETERS_H
