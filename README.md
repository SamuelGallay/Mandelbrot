[![Build status](https://ci.appveyor.com/api/projects/status/pjbeys6p47ln555n?svg=true)](https://ci.appveyor.com/project/SamuelGallay/mandelbrot)


# Mandelbrot

## Introduction

Un simple petit programme en C++/SFML qui permet d'explorer la fractale de Mandelbrot !

## Téléchargement

Des versions déjà compilées en static-32bits pour Windows sont disponnibles [ici](https://github.com/SamuelGallay/Mandelbrot/releases) (environ 400KB).
Sinon il est très simple de le compiler soi-même depuis les sources, avec [CMake](https://cmake.org). Il faut néanmoins avoir installé auparavant la [SFML](https://www.sfml-dev.org) !

## Contrôles

* Les flèches pour se déplacer (Haut, Bas, Droite et Gauche)
* Z pour zoomer
* S pour dézoomer
* F pour augmenter le flou (plus rapide)
* R pour baisser le flou (plus détaillé)
* W pour générer une image détaillée
* I (Itérations) pour augmenter le nombre d'itérations (se rétablit à chaque changement du zoom)
* K pour baisser le nombre d'itérations

* Les captures d'écran ne tiennent pas compte du flou
