#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

#include "Mandelbrot.hpp"

#if SAM_XCODE
#include "ResourcePath.hpp"
#else
#endif

Application::Application():mmWindow(sf::VideoMode(1000, 600), "SFML mWindow"),mmFractale(1000, 600),
mmVitesse(0.6),mmmVitZoom(1,4),mmFlou(1)
{
    mmWindow.setFramerateLimit(30);
}

void Application::run()
{

    
#if SAM_XCODE
    std::string chemin = resourcePath() + "../../../";
#else
    std::string chemin = "";
#endif
    
    while (mWindow.isOpen())
    {
        processEvents();
        render();
    }

}

void Application::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
            if (event.type == sf::Event::Closed)
                mmWindow.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                mWindow.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
                mFractale.move(sf::Vector2f(0, -1*mVitesse));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
                mFractale.move(sf::Vector2f(0, 1*mVitesse));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
                mFractale.move(sf::Vector2f(1*mVitesse, 0));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
                mFractale.move(sf::Vector2f(-1*mVitesse, 0));
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F){
                mFlou *= 2;
                sf::FloatRect visibleArea(0, 0, mWindow.getSize().x, mWindow.getSize().y);
                mWindow.setView(sf::View(visibleArea));
                mFractale.setSize(mWindow.getSize().x/ mFlou, mWindow.getSize().y/ mFlou);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && mFlou > 1){
                mFlou /= 2;
                sf::FloatRect visibleArea(0, 0, mWindow.getSize().x, mWindow.getSize().y);
                mWindow.setView(sf::View(visibleArea));
                mFractale.setSize(mWindow.getSize().x/ mFlou, mWindow.getSize().y/ mFlou);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
                mFractale.setZoom(mFractale.getZoom()*mmVitZoom);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                mFractale.setZoom(mFractale.getZoom()/mmVitZoom);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
                mFractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                mFractale.setSize(mWindow.getSize().x * 2, mWindow.getSize().y * 2);
                mFractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
                mFractale.setSize(mWindow.getSize().x / mFlou, mWindow.getSize().y / mFlou);
            }
            if (event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                mWindow.setView(sf::View(visibleArea));
                mFractale.setSize(event.size.width / mFlou, event.size.height / mFlou);
            }
    }
}

void Application::render()
{
    sf::Image image = mFractale.getImage();
    sf::Texture test;
    test.loadFromImage(image);
    sf::Sprite sprite(test);
    sprite.setScale(static_cast<float>(mFlou), static_cast<float>(mFlou));
    mWindow.clear();
    mWindow.draw(sprite);
    mWindow.display();
}
