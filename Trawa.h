#include "Roslina.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

class Trawa : public Roslina {
public:
    Trawa(Swiat* swiat, int x, int y);
    virtual ~Trawa() {}

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
};