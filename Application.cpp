#include "Application.h"

#include "Mandelbrot.h"

#include <string>
#include <ctime>
#include <iostream>
#include <thread>
#include <cmath>
#include <memory>

Application::Application() : window(sf::VideoMode(1000, 600), "Mandelbrot Render") {
    window.setFramerateLimit(30);

    //Liste des Couleurs
    param.liste.push_back(sf::Color::Black);
    param.liste.push_back(sf::Color::Blue);
    param.liste.push_back(sf::Color::Yellow);
    param.liste.push_back(sf::Color::Magenta);
    param.liste.push_back(sf::Color::Red);
    param.liste.push_back(sf::Color::Yellow);
    param.liste.push_back(sf::Color::Magenta);
    param.liste.push_back(sf::Color::Red);

    //Autres variables necessaires à la fractale
    rendu = std::make_shared<sf::Image>();
    param.definition = window.getSize();
    rendu->create(param.definition.x, param.definition.y);
    param.iterMax = 50;
    param.center = sf::Vector2<double>(-0.75, 0.0);
    param.zoom = 1.0;
    vitesse = 0.6;
    vitZoom = 2.0;
    flou = 1;

    initializeGUI();

    updateInfosGUI();
}

void Application::run() {
    stop_thread = false;
    actualize_rendering = false;

    std::thread worker(&Application::runWorker, this);

    while (window.isOpen()) {
        sf::Time delta = clock.restart();

        Parameters oldParam = param;

        sf::Event event;
        while (window.pollEvent(event)) {
            desktop.HandleEvent(event);
            handleInputs(event);
        }

        desktop.Update(delta.asSeconds());

        if (oldParam.definition != param.definition)
            actualize_rendering = true;

        if (oldParam != param)
            updateInfosGUI();

        if (oldParam.liste != param.liste)
            updateColors();

        sf::Texture test;
        test.loadFromImage(*rendu);
        sf::Sprite sprite(test);
        sprite.setScale(static_cast<float>(flou), static_cast<float>(flou));

        window.clear();
        if(!actualize_rendering)
            window.draw(sprite);
        sfgui.Display(window);
        window.display();
    }
    stop_thread = true;
    actualize_rendering = true;
    worker.join();
}

void Application::handleInputs(sf::Event event) {
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
        param.center.y -= vitesse / param.zoom;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
        param.center.y += vitesse / param.zoom;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
        param.center.x += vitesse / param.zoom;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        param.center.x -= vitesse / param.zoom;
    }
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
    if (event.key.control && event.key.code == sf::Keyboard::V) {
        std::string presse = sf::Clipboard::getString();
        if (l_left->HasFocus())
            l_left->SetText(presse);
        if (l_top->HasFocus())
            l_top->SetText(presse);
    }
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        if (l_left->HasFocus())
            sf::Clipboard::setString(l_left->GetText());
        if (l_top->HasFocus())
            sf::Clipboard::setString(l_top->GetText());
    }
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, (float) event.size.width, (float) event.size.height);
        window.setView(sf::View(visibleArea));
        param.definition.x = window.getSize().x / flou;
        param.definition.y = window.getSize().y / flou;
    }
}

void Application::wallpaper(Parameters c_param) {
    sf::Clock chrono;
    c_param.definition = sf::Vector2<unsigned int>(1920 * 2, 1200 * 2);
    auto temp = std::make_shared<sf::Image>();
    temp->create(1920 * 2, 1200 * 2);
    mandelbrot(temp, c_param, stop_thread);
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

void Application::initializeGUI() {
    // Construction GUI
    l_left = sfg::Entry::Create();
    l_left->SetMaximumLength(50);
    l_top = sfg::Entry::Create();
    l_top->SetMaximumLength(50);
    l_zoom = sfg::SpinButton::Create(0, 100, 1);
    l_iterMax = sfg::SpinButton::Create(0, 100000, 50);
    t_left = sfg::Label::Create();
    t_left->SetText("X");
    t_top = sfg::Label::Create();
    t_top->SetText("Y");
    t_zoom = sfg::Label::Create();
    t_zoom->SetText("Zoom (2^)");
    t_iterMax = sfg::Label::Create();
    t_iterMax->SetText("Iterations");
    boxV1 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    boxV1->Pack(t_left);
    boxV1->Pack(t_top);
    boxV1->Pack(t_zoom);
    boxV1->Pack(t_iterMax);
    boxV1->SetSpacing(5.f);
    boxV2 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    boxV2->Pack(l_left);
    boxV2->Pack(l_top);
    boxV2->Pack(l_zoom);
    boxV2->Pack(l_iterMax);
    boxV2->SetSpacing(5.f);
    boxV2->SetRequisition(sf::Vector2f(100.f, 0.f));
    boxH = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    boxH->SetSpacing(15.f);
    boxH->Pack(boxV1);
    boxH->Pack(boxV2);
    screenshot = sfg::Button::Create();
    screenshot->SetLabel("Screenshot");
    poster = sfg::Button::Create();
    poster->SetLabel("Wallpaper");
    boxH2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    boxH2->Pack(screenshot);
    boxH2->Pack(poster);
    button = sfg::Button::Create();
    button->SetLabel("Compute");
    add_color = sfg::Button::Create();
    add_color->SetLabel("Add Color");
    s_red = sfg::SpinButton::Create(0, 255, 1);
    s_green = sfg::SpinButton::Create(0, 255, 1);
    s_blue = sfg::SpinButton::Create(0, 255, 1);
    boxRGB = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    boxRGB->Pack(s_red);
    boxRGB->Pack(s_green);
    boxRGB->Pack(s_blue);
    boxV = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    boxV->Pack(boxH);
    boxV->Pack(button);
    boxColor = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    boxV->Pack(boxColor);
    boxV->Pack(boxRGB);
    boxV->Pack(add_color);
    boxV->Pack(boxH2);
    boxV->SetSpacing(15.f);
    swindow = sfg::Window::Create();
    swindow->SetTitle("Mandelbrot Set");
    swindow->Add(boxV);
    swindow->SetRequisition(sf::Vector2f(150.f, 0.f));
    desktop.Add(swindow);

    updateColors();

    button->GetSignal(sfg::Button::OnLeftClick).Connect([this] {
        param.iterMax = (int) l_iterMax->GetValue();
        param.zoom = std::pow(2, l_zoom->GetValue());
        try {
            std::string test = l_left->GetText();
            param.center.x = std::stod(test);
        }
        catch (const std::invalid_argument &ia) {
            std::cout << "Hello !!!" << std::endl;
        }
        try {
            std::string test = l_top->GetText();
            param.center.y = std::stod(test);
        }
        catch (const std::invalid_argument &ia) {
            std::cout << "Hello !!!" << std::endl;
        }
    });
    screenshot->GetSignal(sfg::Button::OnLeftClick).Connect([this] {
        rendu->saveToFile(std::to_string(time(NULL)) + ".png");
    });
    poster->GetSignal(sfg::Button::OnLeftClick).Connect([this] {
        std::thread first(&Application::wallpaper, this, param);
        first.detach();
    });
    add_color->GetSignal(sfg::Button::OnLeftClick).Connect([this] {
        param.liste.push_back(sf::Color(s_red->GetValue(), s_green->GetValue(), s_blue->GetValue()));
    });

    auto glambda = [this]() {
        sf::Image temp;
        temp.create(50, 15, sf::Color(s_red->GetValue(), s_green->GetValue(), s_blue->GetValue()));
        auto temp2 = sfg::Image::Create();
        temp2->SetImage(temp);
        add_color->SetImage(temp2);
    };
    glambda();

    swindow->GetSignal(sfg::Window::OnMouseMove).Connect(glambda);

    s_red->GetSignal(sfg::SpinButton::OnValueChanged).Connect(glambda);
    s_blue->GetSignal(sfg::SpinButton::OnValueChanged).Connect(glambda);
    s_green->GetSignal(sfg::SpinButton::OnValueChanged).Connect(glambda);
}

void Application::updateInfosGUI() {
    std::stringstream streamX;
    streamX << std::fixed << std::setprecision(50) << param.center.x;
    l_left->SetText(streamX.str());
    std::stringstream streamY;
    streamY << std::fixed << std::setprecision(50) << param.center.y;
    l_top->SetText(streamY.str());
    l_zoom->SetValue(std::round(std::log((float) param.zoom) / log(2.f)));
    l_iterMax->SetValue((float) param.iterMax);
}

void Application::runWorker() {
    sf::Vector2<unsigned int> oldDefinition = param.definition;

    while (!stop_thread) {
        if (param.definition != oldDefinition) {
            oldDefinition = param.definition;
            rendu->create(param.definition.x, param.definition.y, sf::Color::Black);
            actualize_rendering = false;
        }
        mandelbrot(rendu, param, ref(actualize_rendering));
    }
}

void Application::updateColors() {
    boxColor->RemoveAll();
    listButtons.clear();

    for(int i=0; i<param.liste.size(); i++){
        auto temp = sfg::Button::Create();

        sf::Image a;
        a.create(170, 20, param.liste[i]);

        auto b = sfg::Image::Create();
        b->SetImage(a);
        temp->SetImage(b);

        listButtons.push_back(temp);

        boxColor->Pack(listButtons[i]);
        listButtons[i]->GetSignal(sfg::Button::OnMouseRightPress).Connect([this, i] {
            if (param.liste.size() > 2)
                param.liste.erase(param.liste.begin() + i);
        });
        listButtons[i]->GetSignal(sfg::Button::OnLeftClick).Connect([this, i] {
            param.liste[i] = sf::Color(s_red->GetValue(), s_green->GetValue(), s_blue->GetValue());
        });
    }
    auto ttt = sf::FloatRect(swindow->GetAbsolutePosition(), swindow->GetRequisition());
    swindow->SetAllocation(ttt);
}
