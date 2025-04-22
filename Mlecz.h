#include "Roslina.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

class Mlecz : public Roslina {
public:
    Mlecz(Swiat* swiat, int x, int y);
    virtual ~Mlecz() {}

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
    virtual void akcja() override;
};