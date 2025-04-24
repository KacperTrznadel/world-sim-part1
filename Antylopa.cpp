#include <iostream>
#include "Antylopa.h"
#include "Swiat.h"
using namespace std;

Antylopa::Antylopa(Swiat* swiat, int x, int y) : Zwierze(swiat, 4, 4, x, y, "Antylopa") {}
char Antylopa::rysowanie() const {
    return 'A';
}
Organizm* Antylopa::klonuj(Swiat* swiat, int x, int y) const  {
    return new Antylopa(swiat, x, y);
}
void Antylopa::akcja() {
    wiekInkrementacja();
    int dx[] = { 0, 2, 0, -2 };
    int dy[] = { -2, 0, 2, 0 };

    int kierunki[4] = {0, 1, 2, 3};

    // Tasowanie kierunków
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(kierunki[i], kierunki[j]);
    }

    Swiat* swiat = getSwiat();

    for (int i = 0; i < 4; ++i) {
        int k = kierunki[i];
        
        int newX = getX() + dx[k];
        int newY = getY() + dy[k];

        int oldX = getX();
        int oldY = getY();

        if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
            Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
            if (cel == nullptr) {
                swiat->dodajLog(this->getNazwa() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                setPozycja(newX, newY);
                return;
            } else {
                swiat->dodajLog(this->getNazwa() + string(" probuje wejsc na pole zajmowane przez ") + cel->getNazwa() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                kolizja(cel, oldX, oldY);
                return;
            }
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
            int newX = getX() + dx[i];
            int newY = getY() + dy[i];
            Swiat* swiat = getSwiat();
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                swiat->dodajLog(this->getNazwa() + string(" uciekla przed swoim atakiem na pole (") + to_string(newX) + "," + to_string(newY) + ")");
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
            int newX = getX() + dx[i];
            int newY = getY() + dy[i];
            Swiat* swiat = getSwiat();
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                setPozycja(newX, newY);
                swiat->dodajLog(this->getNazwa() + string(" uciekla przed atakiem na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                return true;
            }
        }
    }
    return false;
}
