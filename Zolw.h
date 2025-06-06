#ifndef ZOLW_H
#define ZOLW_H

#include <iostream>
#include "Zwierze.h"
using namespace std;

class Zolw : public Zwierze {
public:
    Zolw(Swiat* swiat, int x, int y);
    virtual ~Zolw() {};

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;

    virtual void akcja() override;
    virtual bool czyOdbilAtak(Organizm* atakujacy) override;
};

#endif