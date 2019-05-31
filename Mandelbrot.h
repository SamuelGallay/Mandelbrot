#ifndef Mandelbrot_hpp
#define Mandelbrot_hpp

#include "Parameters.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <atomic>

void mandelbrot(
        std::shared_ptr<sf::Image> rendu,
        Parameters param,
        std::atomic_bool &actualize
);

#endif /* Mandelbrot_hpp */
