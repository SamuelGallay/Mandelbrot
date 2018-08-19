#include "Application.hpp"
#include "Mandelbrot.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include "Menu.hpp"

#if SAM_XCODE
#include "ResourcePath.hpp"
std::string chemin = resourcePath() + "../../../";
#else
std::string chemin = "";
#endif

Application::Application(sf::RenderWindow &appWindow):mWindow(&appWindow),mFractale(1000, 600), mVitesse(0.6f) ,mVitZoom(1.4f), mFlou(1)
{
    mWindow->setFramerateLimit(5);
}

void Application::run()
{
    while (mWindow->isOpen())
    {
        processEvents();
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow->close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            Menu menu(*mWindow);
            menu.run();
        }


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
            sf::FloatRect visibleArea(0, 0, static_cast<float>(mWindow->getSize().x), static_cast<float>(mWindow->getSize().y) );
            mWindow->setView(sf::View(visibleArea));
            mFractale.setSize(mWindow->getSize().x/ mFlou, mWindow->getSize().y/ mFlou);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && mFlou > 1){
            mFlou /= 2;
            sf::FloatRect visibleArea(0, 0, static_cast<float>(mWindow->getSize().x), static_cast<float>(mWindow->getSize().y));
            mWindow->setView(sf::View(visibleArea));
            mFractale.setSize(mWindow->getSize().x/ mFlou, mWindow->getSize().y/ mFlou);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
            mFractale.setZoom(mFractale.getZoom()*mVitZoom);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            mFractale.setZoom(mFractale.getZoom()/mVitZoom);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
            mFractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
            mFractale.setSize(mWindow->getSize().x * 2, mWindow->getSize().y * 2);
            mFractale.getImage().saveToFile(chemin + std::to_string(time(NULL)) + ".png");
            mFractale.setSize(mWindow->getSize().x / mFlou, mWindow->getSize().y / mFlou);
            std::cout<<"image enregistrée";
        }
        if (event.type == sf::Event::Resized){
            sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height) );
            mWindow->setView(sf::View(visibleArea));
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
    mWindow->clear();
    mWindow->draw(sprite);
    mWindow->display();
}
