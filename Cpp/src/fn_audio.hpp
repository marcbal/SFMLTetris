#ifndef FN_AUDIO_H
#define FN_AUDIO_H

#include "headers.hpp"







/*
Excerpted from "C++ Cookbook" by Ryan Stephens, Christopher Diggins,
Jonathan Turkanis, and Jeff Cogswell. Copyright C 2006 O'Reilly Media, Inc.
All rights reserved.
Published by O'Reilly Media, Inc.
To purchase this book go to: http://oreilly.com/catalog/9780596007614/
*/

const double PI = 3.1415926536;  //obligation de définir PI car il n'est pas obligé qu'elle soit définie.
unsigned int bitReverse(unsigned int x, int log2n);
void fft(complex<double> * a, complex<double> * b, int log2n);


#endif // FN_AUDIO_H
