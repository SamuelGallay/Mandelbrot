#include "Application.h"

#include "Mandelbrot.h"

#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <cmath>
#include <memory>

Application::Application() : window(sf::VideoMode(1000, 600), "Mandelbrot Render") {
    window.setFramerateLimit(30);

    rendu = std::make_shared<sf::Image>();
    rendu->create(param.definition.x, param.definition.y);

    vitesse = 0.6;
    vitZoom = 2.0;
    flou = 1;

    mandelbrot(rendu, param);
    gui.setParameters(param);
}

void Application::run() {
    std::thread worker(&Application::runWorker, this);
    worker.detach();

    while (window.isOpen()) {
        sf::Time delta = clock.restart();

        Parameters oldParam = param;

        sf::Event event;
        while (window.pollEvent(event)) {
            handleInputs(event);
        }

        if (param != oldParam)
            gui.setParameters(param);

        sf::Texture texture;
        texture.loadFromImage(*rendu);
        sf::Sprite sprite(texture);
        sprite.setScale(static_cast<float>(flou), static_cast<float>(flou));

        window.clear();
        window.draw(sprite);
        window.draw(gui);
        window.display();
    }
}

void Application::runWorker() {
    sf::Vector2<unsigned int> oldDefinition = param.definition;
    Parameters oldParam = param;

    while (true) {
        if (param != oldParam) {
            oldParam = param;
            if (param.definition != oldDefinition) {
                oldDefinition = param.definition;
                rendu->create(param.definition.x, param.definition.y, sf::Color::Black);
            }
            mandelbrot(rendu, param);
        } else {
            std::chrono::milliseconds timespan(20);
            std::this_thread::sleep_for(timespan);
        }
    }
}

void Application::handleInputs(sf::Event event) {
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        param.center.y -= vitesse / param.zoom;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        param.center.y += vitesse / param.zoom;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        param.center.x += vitesse / param.zoom;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        param.center.x -= vitesse / param.zoom;

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
        flou *= 2;
        param.definition.x = window.getSize().x / flou;
        param.definition.y = window.getSize().y / flou;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && flou > 1) {
        flou /= 2;
        param.definition.x = window.getSize().x / flou;
        param.definition.y = window.getSize().y / flou;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
        param.zoom *= vitZoom;
        param.iterMax = (int) (100 * std::log(param.zoom + 1));
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
        param.zoom /= vitZoom;
        param.iterMax = (int) (100 * std::log(param.zoom + 1));
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
        param.iterMax *= 1.1;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
        param.iterMax /= 1.1;
    }

    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, (float) event.size.width, (float) event.size.height);
        window.setView(sf::View(visibleArea));
        param.definition.x = window.getSize().x / flou;
        param.definition.y = window.getSize().y / flou;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
        std::thread worker2(&Application::wallpaper, this, param);
        worker2.detach();
    }
}

void Application::wallpaper(Parameters c_param) {
    sf::Clock chrono;
    c_param.definition = sf::Vector2<unsigned int>(1920 * 2, 1200 * 2);
    auto temp = std::make_shared<sf::Image>();
    temp->create(1920 * 2, 1200 * 2);
    mandelbrot(temp, c_param);
    sf::Image poster;
    poster.create(1920, 1200);
    for (int y = 0; y < 1200; y++) {
        for (int x = 0; x < 1920; x++) {
            int r = 0, g = 0, b = 0;
            sf::Color c1 = temp->getPixel(x * 2, y * 2);
            sf::Color c2 = temp->getPixel(x * 2 + 1, y * 2);
            sf::Color c3 = temp->getPixel(x * 2, y * 2 + 1);
            sf::Color c4 = temp->getPixel(x * 2 + 1, y * 2 + 1);
            r = (c1.r + c2.r + c3.r + c4.r) / 4;
            g = (c1.g + c2.g + c3.g + c4.g) / 4;
            b = (c1.b + c2.b + c3.b + c4.b) / 4;
            poster.setPixel(x, y, sf::Color(r, g, b));
        }
    }
    poster.saveToFile(std::to_string(time(NULL)) + ".png");
    std::cout << "Wallpaper saved in : " << std::to_string(chrono.restart().asSeconds()) << "s\n";
}
