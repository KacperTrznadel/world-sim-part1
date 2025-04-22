#include "Roslina.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

class WilczeJagody : public Roslina {
public:
    WilczeJagody(Swiat* swiat, int x, int y);
    virtual ~WilczeJagody() {}

    virtual char rysowanie() const override;
    virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
    virtual void kolizja(Organizm* inny, int oldX, int oldY) override;
};