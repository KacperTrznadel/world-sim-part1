#ifndef WILK_H
#define WILK_H

#include <iostream>
#include "Zwierze.h"
using namespace std;

class Wilk : public Zwierze {
public:
    Wilk(Swiat* swiat, int x, int y);
    virtual ~Wilk() {};

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(int x, int y) const override;
};

#endif