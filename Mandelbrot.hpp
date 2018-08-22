#ifndef Mandelbrot_hpp
#define Mandelbrot_hpp

#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

#include "SFML/Graphics.hpp"

class Mandelbrot
{
public:
    Mandelbrot(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    void setZoom(double ratio);
    void move(sf::Vector2f direction);
	void setColors(std::vector<sf::Color> newList);
	
    double getZoom(){
        return zoom;
    }
    sf::Image getImage(){
        return rendu;
    }
	std::vector<sf::Color> getColors(){
		return liste;
	}
	

private:
    std::vector<sf::Color> liste;
    void update();
    void render();
    sf::Image rendu;
    std::vector<unsigned int> iterations;
    unsigned int iterMax;
    sf::Rect<double> vue;
    double zoom;
};

#endif /* Mandelbrot_hpp */
