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

Install [Mingw GCC 6.1.0 (32 bits)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/6.1.0/threads-posix/dwarf/i686-6.1.0-release-posix-dwarf-rt_v5-rev0.7z/download).
From here, you have 2 options:

* Add the `<mingw-install-dir>/bin` directory in your PATH environment variable,
* Or put the absolute path of the compiler in the file `Cpp/Makefile.win`.

Finally, go to the `Cpp` folder and compile with `make -f Makefile.win release`. You can find the build project in `bin/release_w/`

This projet is not yet set up for 64 bits compilation on Windows.

### Linux

As of april 2024, it only works on Ubuntu 16.04 (more recent OS are shipped with not old enough compiler/libraries).
Install the necessary packages: `sudo apt install make g++-5 libglu1-mesa-dev libopenal-dev`.
Newer build environment does not yet work for this project.
On linux, 32 bit is not supported.


## Useful links while making the game

A Wiki giving guideling for making a standard tetris game: http://tetris.wikia.com/wiki/Tetris_Guideline

Tutorial to make a simple tetris game in C (fr): http://tfeysal.wordpress.com/2011/01/10/programmer-un-tetris-en-c-partie-1/
(there is no part 2)

The Tetris wikipedia article (fr): http://fr.wikipedia.org/wiki/Tetris
