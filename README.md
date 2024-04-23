# SFMLTetris

A Tetris game made in C++ with the [SFML library](https://www.sfml-dev.org/index.php).
It was a project for an IT university course in 2014 (DUT Informatique, IUT de Lens, Université d’Artois).

Website : http://sfmltetris.pandacube.fr/

## Contributors

- Louis Behague (Babanar) : developer
- Marc Baloup (marcbal) : developer, project manager
- Mathieu Blanquin (Devil62) : mock-ups and old project manager

## How to build

### Windows

As of april 2024, on Windows 10 22H2.
Install CodeBlocks 16.01 with the included Mingw build environment (4.9.2 win32).
Newer build environment does not yet work for this project.
This projet is not yet set up for 64 bits compilation on Windows.

### Linux

As of april 2024, it only works on Ubuntu 14.04 (more recent OS are shipped with not old enough compiler/libraries).
Install `apt install codeblocks g++ libglu1-mesa-dev libopenal-dev`.
The g++ version should be 4.8.x.
Newer build environment does not yet work for this project.
On linux, the project is only compiled for 64 bits architecture (not 32 like on Windows).


## Useful links while making the game

A Wiki giving guideling for making a standard tetris game: http://tetris.wikia.com/wiki/Tetris_Guideline

Tutorial to make a simple tetris game in C (fr): http://tfeysal.wordpress.com/2011/01/10/programmer-un-tetris-en-c-partie-1/
(there is no part 2)

The Tetris wikipedia article (fr): http://fr.wikipedia.org/wiki/Tetris
