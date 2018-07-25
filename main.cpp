#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

#include "Mandelbrot.hpp"

#if SAM_XCODE
#include "ResourcePath.hpp"
#else
#endif

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML window");
    window.setFramerateLimit(30);
    Mandelbrot fractale(1000, 600);
    
    #if SAM_XCODE
    std::string chemin = resourcePath() + "../../../";
    #else
    std::string chemin = "";
    #endif
    
    float vitesse = 0.6;
    float vitZoom = 1.4;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
                fractale.move(sf::Vector2f(0, -1*vitesse));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
                fractale.move(sf::Vector2f(0, 1*vitesse));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
                fractale.move(sf::Vector2f(1*vitesse, 0));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
                fractale.move(sf::Vector2f(-1*vitesse, 0));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
                fractale.setZoom(fractale.getZoom()*vitZoom);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
                fractale.setZoom(fractale.getZoom()/vitZoom);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                fractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                fractale.setSize(window.getSize().x * 4, window.getSize().y * 4);
                fractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
                fractale.setSize(window.getSize().x, window.getSize().y);
            }
            if (event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                fractale.setSize(event.size.width, event.size.height);
            }
        }
        sf:: Image image = fractale.getImage();
        sf::Texture test;
        test.loadFromImage(image);
        window.clear();
        window.draw(sf::Sprite(test));
        window.display();
    }
    return EXIT_SUCCESS;
}
