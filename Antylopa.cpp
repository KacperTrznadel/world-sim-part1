#include <iostream>
#include "Antylopa.h"
using namespace std;

Antylopa::Antylopa(Swiat* swiat, int x, int y) : Zwierze(swiat, 4, 4, x, y) {}
char Antylopa::rysowanie() const {
    return 'A';
}
Organizm* Antylopa::klonuj(int x, int y) const {
    return new Antylopa(swiat, x, y);
}
void Antylopa::akcja() {
    wiekInkrementacja();
    int dx[] = { 0, 2, 0, -2 };
    int dy[] = { -2, 0, 2, 0 };

    int kierunek = rand() % 4;

    int newX = x + dx[kierunek];
    int newY = y + dy[kierunek];

    if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
        Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
        if (cel == nullptr) {
            setPozycja(newX, newY);
        } else {
            int oldX = x;
            int oldY = y;
            kolizja(cel, oldX, oldY);
        }
    }
}
void Antylopa::kolizja(Organizm* inny, int oldX, int oldY) {
    //50% szans na ucieczkę, gdy Antylopa spotka inny organizm
    int ucieczka = rand() % 2;
    if (ucieczka == 0) {
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                setPozycja(newX, newY);
                return;
            }
        }
        return;
    }

    Zwierze::kolizja(inny, oldX, oldY);

}
bool Antylopa::czyOdbilAtak(Organizm* atakujacy) {
    //50% szans na ucieczkę, gdy Antylopa zostanie zaatakowana
    if (rand() % 2 == 0) {
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                setPozycja(newX, newY);
                cout << "Antylopa uciekla przed atakiem!" << endl;
                return true;
            }
        }
    }
    return false;
}
