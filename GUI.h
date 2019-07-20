#ifndef MANDELBROT_GUI_H
#define MANDELBROT_GUI_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Parameters.h"

class GUI : public sf::Drawable, public sf::Transformable {
public:
    GUI();

    void setParameters(Parameters param);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Font font;
    sf::Text text;
};


#endif //MANDELBROT_GUI_H
