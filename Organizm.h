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
        string nazwa;
        Swiat* swiat;
        bool zywy = true;

    public:

        Organizm(Swiat* swiat, int sila, int inicjatywa, int x, int y, string nazwa);
        virtual ~Organizm();
        
        virtual void akcja() = 0;
        virtual void kolizja(Organizm* inny, int oldX, int oldY) = 0;
        virtual bool czyOdbilAtak(Organizm* atakujacy) { return false; }
        virtual char rysowanie() const = 0;
        virtual Organizm* klonuj(Swiat* swiat, int x, int y) const = 0;


        int getSila() const;
        int getInicjatywa() const;
        int getX() const;
        int getY() const;
        string getNazwa() const;
        Swiat* getSwiat() const;
        int getWiek() const;
        bool czyZywy() const;

        void setSila(int sila);
        void setPozycja(int newX, int newY);
        void wiekInkrementacja();
        void setWiek(int wiek) { this->wiek = wiek; }
        void zabij();

};

#endif