#ifndef MANDELBROT_APPLICATION_H
#define MANDELBROT_APPLICATION_H

#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <atomic>

#include "Parameters.h"

class Application {
public:
    Application();

    void run();

private:
    void
    wallpaper(Parameters c_param);

    void handleInputs(sf::Event event);

    void initializeGUI();

    void updateInfosGUI();

    void runWorker();

    void updateColors();

    sfg::SFGUI sfgui;
    sf::RenderWindow window;
    std::shared_ptr<sf::Image> rendu;
    double vitesse;
    double vitZoom;
    int flou;
    sf::Clock clock;

    std::atomic_bool stop_thread;
    std::atomic_bool actualize_rendering;

    Parameters param;

    sfg::Desktop desktop;
    std::vector<sfg::Button::Ptr> listButtons;

    sfg::Entry::Ptr l_left;
    sfg::Entry::Ptr l_top;

    sfg::SpinButton::Ptr l_zoom;
    sfg::SpinButton::Ptr l_iterMax;
    sfg::SpinButton::Ptr s_red;
    sfg::SpinButton::Ptr s_green;
    sfg::SpinButton::Ptr s_blue;

    sfg::Label::Ptr t_left;
    sfg::Label::Ptr t_top;
    sfg::Label::Ptr t_zoom;
    sfg::Label::Ptr t_iterMax;

    sfg::Box::Ptr boxV1;
    sfg::Box::Ptr boxV2;
    sfg::Box::Ptr boxH;
    sfg::Box::Ptr boxH2;
    sfg::Box::Ptr boxV;
    sfg::Box::Ptr boxColor;
    sfg::Box::Ptr boxRGB;

    sfg::Button::Ptr screenshot;
    sfg::Button::Ptr poster;
    sfg::CheckButton::Ptr check_button;
    sfg::Button::Ptr button;
    sfg::Button::Ptr add_color;
    sfg::Window::Ptr swindow;
};


#endif //MANDELBROT_APPLICATION_H
