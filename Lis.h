#ifndef LIS_H
#define LIS_H

#include <iostream>
#include "Zwierze.h"
using namespace std;

class Lis : public Zwierze {
public:
    Lis(Swiat* swiat, int x, int y);
    virtual ~Lis() {};

    virtual void akcja() override;
    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
};

#endif