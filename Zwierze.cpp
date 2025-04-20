#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>

Zwierze::Zwierze(Swiat* swiat, int sila, int inicjatywa, int x, int y)
    : Organizm(swiat, sila, inicjatywa, x, y) {}

void Zwierze::akcja() {

    wiekInkrementacja();
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };
    int kierunek = rand() % 4;

    int oldX = getX();
    int oldY = getY();

    int newX = oldX + dx[kierunek];
    int newY = oldY + dy[kierunek];

    Swiat* swiat = getSwiat();

    if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {

        Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
        if (cel == nullptr) {
            setPozycja(newX, newY);
        } else {
            kolizja(cel, oldX, oldY);
        }
    }
}

void Zwierze::kolizja(Organizm* inny, int oldX, int oldY) {
    if (typeid(*this) == typeid(*inny)) {

        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; i++) {
            int newX = getX() + dx[i];
            int newY = getY() + dy[i];
            Swiat* swiat = getSwiat();
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                
                Organizm* potomek = this->klonuj(swiat, newX, newY);
                swiat->dodajOrganizm(potomek);
                return;
            }
        }

        return;
    }

    // Próba ataku
    if (inny->czyOdbilAtak(this)) {
        setPozycja(oldX, oldY);
        return;
    }

    // Zwykła walka
    if (this->getSila() >= inny->getSila()) {
        inny->zabij();
        setPozycja(inny->getX(), inny->getY());
    } else {
        this->zabij();
    }
}
