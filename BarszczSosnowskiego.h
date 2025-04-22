#ifndef BARSZCZSOSNOWSKIEGO_H
#define BARSZCZSOSNOWSKIEGO_H
#include "Roslina.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

class BarszczSosnowskiego : public Roslina {
public:
    BarszczSosnowskiego(Swiat* swiat, int x, int y);
    virtual ~BarszczSosnowskiego() {}

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
    virtual void akcja() override;
    virtual void kolizja(Organizm* inny, int oldX, int oldY) override;
};
#endif
