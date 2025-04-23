#include "Zwierze.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

class Czlowiek : public Zwierze {
    public:
        Czlowiek(Swiat* swiat, int x, int y);
        virtual ~Czlowiek() {};

        virtual void akcja() override;
        virtual void kolizja(Organizm* atakujacy) override;
        void tarczaAlzurda();
        virtual char rysowanie() override;
}