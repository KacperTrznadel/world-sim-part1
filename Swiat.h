#ifndef SWIAT_H
#define SWIAT_H

#include <iostream>
#include <vector>
#include "Organizm.h"
using namespace std;

class Swiat {
    private:
        
        int szerokoscPlanszy;
        int wysokoscPlanszy;
        vector<Organizm*> organizmy;
        void wykonajWszystkieAkcje();
        void sprawdzWszystkieKolizje();
        void usunWszystkieMartwe();

    public:

        Swiat(int szerokoscPlanszy, int wysokoscPlanszy);
        ~Swiat();

        void wykonajTure();
        void rysujSwiat() const;
        void dodajOrganizm(Organizm* org);
        
        Organizm* getOrganizmNaPolu(int x, int y) const;
        int getSzerokosc() const;
        int getWysokosc() const;
};

#endif