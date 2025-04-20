#ifndef ZWIERZE_H
#define ZWIERZE_H

#include <iostream>
#include "Organizm.h"
using namespace std;

class Zwierze: public Organizm {

    public:
    Zwierze(Swiat* swiat, int sila, int inicjatywa, int x, int y);
    virtual ~Zwierze() {}

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny, int oldX, int oldY) override;

};

#endif