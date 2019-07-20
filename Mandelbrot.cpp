#include "Mandelbrot.h"

#include <cassert>
#include <complex>
#include <cmath>

void mandelbrot(std::shared_ptr<sf::Image> rendu, Parameters param) {
    sf::Rect<double> vue;
    if (static_cast<double>(param.definition.x) / static_cast<double>(param.definition.y) >= 1.0) {
        vue.width = 2.7 * static_cast<double>(param.definition.x) / static_cast<double>(param.definition.y);
        vue.height = 2.4;
    } else {
        vue.width = 2.7;
        vue.height = 2.4 * static_cast<double>(param.definition.y) / static_cast<double>(param.definition.x);
    }
    vue.left = param.center.x;
    vue.top = param.center.y;

    assert(param.liste.size() >= 2);

    for (unsigned int abscisse = 0; abscisse < param.definition.x; abscisse++) {
        for (unsigned int ordonnee = 0; ordonnee < param.definition.y; ordonnee++) {
            std::complex<double> c(
                    (static_cast<double>(abscisse) / static_cast<double>(param.definition.x) * vue.width / param.zoom +
                     vue.left -
                     vue.width / param.zoom / 2),
                    (static_cast<double>(ordonnee) / static_cast<double>(param.definition.y) * vue.height / param.zoom +
                     vue.top -
                     vue.height / param.zoom / 2));
            std::complex<double> z(0.0, 0.0);
            unsigned int i = 0;

            if ((c.real() + 1) * (c.real() + 1) + c.imag() * c.imag() < 0.0625)
                i = param.iterMax;
            if (c.real() < sqrt((c.real() - 0.25) * (c.real() - 0.25) + c.imag() * c.imag()) - 2 * ((c.real() - 0.25) *
                                                                                                    (c.real() - 0.25) +
                                                                                                    c.imag() *
                                                                                                    c.imag()) + 0.25)
                i = param.iterMax;

            while (std::norm(z) < 256 && i < param.iterMax) {
                z = z * z + c;
                i++;
            }

            float distAbs = (float) i / (float) param.iterMax;

            int depart = param.liste.size() - 1;
            int arrivee = 0;

            while (static_cast<float>(depart) / static_cast<float>(param.liste.size() - 1) > distAbs) { depart--; }
            while (static_cast<float>(arrivee) / static_cast<float>(param.liste.size() - 1) < distAbs) { arrivee++; }

            float distRel =
                    (distAbs - static_cast<float>(depart) / static_cast<float>(param.liste.size() - 1)) *
                    (param.liste.size() - 1);

            sf::Color couleur;
            if (i == param.iterMax)
                couleur = sf::Color::Black;
            else {
                couleur.r = (int) (param.liste[depart].r + (param.liste[arrivee].r - param.liste[depart].r) * distRel);
                couleur.g = (int) (param.liste[depart].g + (param.liste[arrivee].g - param.liste[depart].g) * distRel);
                couleur.b = (int) (param.liste[depart].b + (param.liste[arrivee].b - param.liste[depart].b) * distRel);
            }
            rendu->setPixel(abscisse, ordonnee, couleur);
        }
    }


}
