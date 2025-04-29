#include "Zwierze.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

class Czlowiek : public Zwierze {
    private:
        bool tarczaAktywna = false;
        int dzialanieTarczy = 5;
        int cooldown = 0;

    public:
        Czlowiek(Swiat* swiat, int x, int y);
        virtual ~Czlowiek() {};

        virtual void akcja() override;
        virtual void kolizja(Organizm* atakujacy, int oldX, int oldY) override;
        virtual bool czyOdbilAtak(Organizm* atakujacy) override;
        bool czyTarczaAktywna() const;
        void setTarczaAktywna(bool aktywna);
        void setCooldown(int cooldown);
        int getCooldown() const;
        int getDzialanieTarczy() const;
        void setDzialanieTarczy(int dzialanie);
        virtual char rysowanie() const override;
        virtual Organizm* klonuj(Swiat* swiat, int x, int y) const override;
};