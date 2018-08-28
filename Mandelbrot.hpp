#ifndef Mandelbrot_hpp
#define Mandelbrot_hpp

#include <vector>
#include <cmath>
#include <complex>

#include "SFML/Graphics.hpp"

class Mandelbrot
{
public:
    Mandelbrot(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    
    void setZoom(double ratio){
        zoom = ratio;
        iterMax = (int)(200*std::pow(ratio, 1.0/4.0));
        update();
    }
    void setIter(int a){
        iterMax = a;
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
    std::vector<sf::Color> liste;
    void update();
    void render();
    void basePoint();
    sf::Image rendu;
    std::vector<unsigned int> iterations;
    unsigned int iterMax;
    sf::Rect<double> vue;
    double zoom;
    std::complex<double> x;
    std::vector< std::complex<double> > xn;
    bool optimal;
};

#endif /* Mandelbrot_hpp */
