# SFMLTetris

A Tetris game made in C++ with the [SFML library](https://www.sfml-dev.org/index.php).
It was a project for an IT university course in 2014 (DUT Informatique, IUT de Lens, Université d’Artois).

Website : https://sfmltetris.mbaloup.fr/

## Contributors

- Louis Behague (Babanar) : developer
- Marc Baloup (marcbal) : developer, project manager
- Mathieu Blanquin (Devil62) : mock-ups and old project manager

## How to build

### Windows

This projet is not yet set up for 64 bits compilation on Windows.

* Install [Mingw-w64 (winlibs) GCC 13.1.0 (32-bit)](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-i686-posix-dwarf-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z). Here, you have 2 options:
  * Add the `<mingw-install-dir>/bin` directory in your PATH environment variable,
  * Or put the absolute path of the compiler in the file `Cpp/Makefile.win`.

* Go to the `Cpp` folder and compile with `mingw32-make -f Makefile.win release`.
* You can find the built project in `bin/win32-release`.

### Linux

Works on Ubuntu 24.04 LTS (with GCC 13 and SFML 2.6.1 in the apt repository).
* Install the necessary packages: `sudo apt install make g++-13 libglu1-mesa-dev libopenal-dev libsfml-dev`.
* Go to the `Cpp` folder and compile with `make -f Makefile.linux release`.
* You can find the built project in `bin/linux64-release`.

### Linux via Docker

You can build the Linux version from any OS supporting Docker.
You need to have Docker installed and running (Docker Desktop on Windows).
On Windows, you also need Git-Bash, to run the provided Bash script.

* Go to the `Cpp` folder and run `./make-linux64-with-docker.sh release`.
* You can find the built project in `bin/linux64-release`.


## Resources we used to make the game

A Wiki giving guideling for making a standard tetris game: http://tetris.wikia.com/wiki/Tetris_Guideline

Tutorial to make a simple tetris game in C (fr): http://tfeysal.wordpress.com/2011/01/10/programmer-un-tetris-en-c-partie-1/
(there is no part 2)

The Tetris wikipedia article (fr): http://fr.wikipedia.org/wiki/Tetris
