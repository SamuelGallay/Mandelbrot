#include "Application.hpp"
#include "Menu.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Fractales");
    Menu acceuil(window);
    acceuil.run();
    if(acceuil.getOk())
    {
        Application objet(window);
        objet.run();
    }
}
