#include "Application.hpp"
#include "Menu.hpp"

int main()
{
    Menu accueil;
    accueil.run();
    if(accueil.getOk())
    {
        Application objet;
        objet.run();
    }
}
