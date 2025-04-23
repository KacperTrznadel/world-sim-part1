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
        bool czyTarczaAktywna() const { return tarczaAktywna; }
        void setTarczaAktywna(bool aktywna) { tarczaAktywna = aktywna; }
        void setCooldown(int cooldown) { this->cooldown = cooldown; }
        int getCooldown() const { return cooldown; }
        int getDzialanieTarczy() const { return dzialanieTarczy; }
        void setDzialanieTarczy(int dzialanie) { this->dzialanieTarczy = dzialanie; }
        void tarczaAlzura();
        virtual char rysowanie() override;
}