#ifndef ROSLINA_H
#define ROSLINA_H
#include <iostream>
#include "Organizm.h"
using namespace std;

class Roslina : public Organizm {
public:
    Roslina(Swiat* swiat, int sila, int x, int y);
    virtual ~Roslina() {}

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny, int oldX, int oldY) override;
    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
};
#endif