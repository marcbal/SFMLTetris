#include "fn_audio.hpp"

/*
Excerpted from "C++ Cookbook" by Ryan Stephens, Christopher Diggins,
Jonathan Turkanis, and Jeff Cogswell. Copyright C 2006 O'Reilly Media, Inc.
All rights reserved.
Published by O'Reilly Media, Inc.
To purchase this book go to: http://oreilly.com/catalog/9780596007614/
*/


unsigned int bitReverse(unsigned int x, int log2n)
{
    int n = 0;
    for (int i=0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

void fft(complex<double>* a, complex<double>* b, int log2n)
{
    //typedef typename std::iterator_traits<Iter_T>::value_type complex;
    const complex<double> J(0, 1);
    int n = 1 << log2n;
    for (int i=0; i < n; ++i) {
        b[bitReverse(i, log2n)] = a[i];
    }
    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s;
        int m2 = m >> 1;
        complex<double> w(1, 0);
        complex<double> wm = exp(-J * (PI / m2));
        for (int j=0; j < m2; ++j) {
            for (int k=j; k < n; k += m) {
                complex<double> t = w * b[k + m2];
                complex<double> u = b[k];
                b[k] = u + t;
                b[k + m2] = u - t;
            }
            w *= wm;
        }
    }
}

