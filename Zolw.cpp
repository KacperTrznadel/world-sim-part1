#include <iostream>
#include "Zolw.h"
#include "Swiat.h"
using namespace std;

Zolw::Zolw(Swiat* swiat, int x, int y) : Zwierze(swiat, 2, 1, x, y) {}
char Zolw::rysowanie() const {
    return 'Z';
}
Organizm* Zolw::klonuj(Swiat* swiat, int x, int y) const  {
    return new Zolw(swiat, x, y);
}
void Zolw::akcja() {
    
    int ruch = rand() % 4;
    if (ruch != 0) {
        wiekInkrementacja();
        return;
    }
    
    Zwierze::akcja();
}
bool Zolw::czyOdbilAtak(Organizm* atakujacy) {
    if (atakujacy->getSila() < 5) {
        cout << "Zolw odbil atak!" << endl;
        return true;
    }
    return false;
}