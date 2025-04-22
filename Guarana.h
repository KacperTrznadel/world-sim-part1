#ifndef GUARANA_H
#define GUARANA_H
#include <iostream>
#include "Roslina.h"
using namespace std;

class Guarana : public Roslina {
public:
    Guarana(Swiat* swiat, int x, int y);
    virtual ~Guarana() {}

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
    virtual void kolizja(Organizm* inny, int oldX, int oldY) override;
};
#endif