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
    Mandelbrot();
    Mandelbrot(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    void setZoom(double ratio){
        zoom = ratio;
        iterMax = 100*std::log(ratio+1);
        update();
    }
    void move(sf::Vector2f direction){
        vue.left += direction.x / zoom;
        vue.top += direction.y / zoom;
        update();
    }
    double getZoom(){
        return zoom;
    }
    sf::Image getImage(){
        return rendu;
    }
    
private:
    void update();
    void render();
    sf::Image rendu;
    std::vector<unsigned int> iterations;
    unsigned int iterMax;
    sf::Rect<double> vue;
    double zoom;
};

#endif /* Mandelbrot_hpp */
