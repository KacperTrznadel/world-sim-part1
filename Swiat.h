#ifndef SWIAT_H
#define SWIAT_H

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <fstream>
#include "Organizm.h"
using namespace std;

class Swiat {
    private:
        
        int szerokoscPlanszy;
        int wysokoscPlanszy;
        vector<Organizm*> organizmy;
        vector<Organizm*> noweOrganizmy;
        vector<string> logi;

        WINDOW* gameWin;
        WINDOW* logWin;

        void wykonajWszystkieAkcje();
        void usunWszystkieMartwe();
        void sortujOrganizmy();

    public:

        Swiat(int szerokoscPlanszy, int wysokoscPlanszy);
        ~Swiat();

        void zapiszDoPliku(string nazwaPliku);
        void wczytajZPliku(string nazwaPliku);
        void wykonajTure();
        void rysujSwiat() const;
        void dodajOrganizm(Organizm* org);
        void dodajLog(string tekst);
        void wypiszLogi(int offset) const;

        void inicjalizujOkna();
        void zakonczOkna();
        
        Organizm* getOrganizmNaPolu(int x, int y) const;
        int getSzerokosc() const;
        int getWysokosc() const;
        WINDOW* getGameWin() const { return gameWin; }
        WINDOW* getLogWin() const { return logWin; }
        vector<string> getLogi() const { return logi; }
};

#endif