#ifndef ORGANIZM_H
#define ORGANIZM_H

#include <iostream>
using namespace std;

class Swiat;

class Organizm {
    private:
        int sila;
        int inicjatywa;
        int x, y;
        int wiek = 0;
        Swiat* swiat;
        bool zywy = true;

    public:

        Organizm(Swiat* swiat, int sila, int inicjatywa, int x, int y);
        virtual ~Organizm();
        
        virtual void akcja() = 0;
        virtual void kolizja(Organizm* inny) = 0;
        virtual bool czyOdbilAtak(Organizm* atakujacy) { return false; }
        virtual char rysowanie() const = 0;
        virtual Organizm* klonuj(int x, int y) const = 0;


        int getSila() const;
        int getInicjatywa() const;
        int getX() const;
        int getY() const;
        int getWiek() const;
        bool czyZywy() const;

        void setSila(int sila);
        void setPozycja(int newX, int newY);
        void wiekInkrementacja();
        void zabij();

};

#endif