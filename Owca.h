#ifndef OWCA_H
#define OWCA_H

#include <iostream>
#include "Zwierze.h"
using namespace std;

class Owca : public Zwierze {
public:
    Owca(Swiat* swiat, int x, int y);
    virtual ~Owca() {};

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(int x, int y) const override;
};

#endif