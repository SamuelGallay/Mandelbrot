#ifndef Mandelbrot_hpp
#define Mandelbrot_hpp

#include "Parameters.h"

#include <SFML/Graphics.hpp>
#include <memory>

void mandelbrot(
        std::shared_ptr<sf::Image> rendu,
        Parameters param
);

#endif /* Mandelbrot_hpp */
