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
    
    double vitesse = 0.6; //déplacement
    double vitZoom = 1.4;
    
    int flou = 1;
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F){
                flou *= 2;
                sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
                window.setView(sf::View(visibleArea));
                fractale.setSize(window.getSize().x/ flou, window.getSize().y/ flou);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && flou > 1){
                flou /= 2;
                sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
                window.setView(sf::View(visibleArea));
                fractale.setSize(window.getSize().x/ flou, window.getSize().y/ flou);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
                fractale.setZoom(fractale.getZoom()*vitZoom);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                fractale.setZoom(fractale.getZoom()/vitZoom);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
                fractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                fractale.setSize(window.getSize().x * 2, window.getSize().y * 2);
                fractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
                fractale.setSize(window.getSize().x / flou, window.getSize().y / flou);
            }
            if (event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                fractale.setSize(event.size.width / flou, event.size.height / flou);
            }
        }
        sf:: Image image = fractale.getImage();
        sf::Texture test;
        test.loadFromImage(image);
        sf::Sprite sprite(test);
        sprite.setScale(static_cast<float>(flou), static_cast<float>(flou));
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return EXIT_SUCCESS;
}
