#ifndef ANTYLOPA_H
#define ANTYLOPA_H

#include <iostream>
#include "Zwierze.h"
using namespace std;

class Antylopa : public Zwierze {
public:
    Antylopa(Swiat* swiat, int x, int y);
    virtual ~Antylopa() {};

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
    virtual void akcja() override;
    virtual void kolizja(Organizm* inny, int oldX, int oldY) override;
    virtual bool czyOdbilAtak(Organizm* atakujacy) override;

};

#endif