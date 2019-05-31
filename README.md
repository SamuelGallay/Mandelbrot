[![Build status](https://ci.appveyor.com/api/projects/status/pjbeys6p47ln555n?svg=true)](https://ci.appveyor.com/project/SamuelGallay/mandelbrot)


# Mandelbrot

## Introduction

Un simple petit programme en C++/SFML qui permet d'explorer la fractale de Mandelbrot !

## Téléchargement

Des versions déjà compilées en static-32bits pour Windows sont disponnibles [ici](https://github.com/SamuelGallay/Mandelbrot/releases) (environ 400KB).
Sinon il est très simple de le compiler soi-même depuis les sources, avec [CMake](https://cmake.org). Il faut néanmoins avoir installé auparavant la 
[SFML](https://www.sfml-dev.org), et [SFGUI](https://github.com/TankOs/SFGUI) !

## Contrôles 

* Les flèches pour se déplacer (Haut, Bas, Droite et Gauche)

* Z pour zoomer

* S pour dézoomer

* F pour augmenter le flou (plus rapide, mais plus "pixellisé")

* R pour baisser le flou (plus détaillé, mais plus lent)

* Les captures d'écran ne tiennent pas compte du flou

Il est aussi possible de changer les couleurs : 

* Les couleurs sont classées de celles les plus lointaines de la fractale à celles les plus proches

* Un clique-droit sur une couleur la supprime

* Un clique gauche lui fait prendre la couleur RVB entrée dans les 3 cases en dessous.

* Ces 3 cases prennent les valeurs de rouge, de vert et de bleu, comprises entre 0 et 255
