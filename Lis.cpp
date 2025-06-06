#include <iostream>
#include "Lis.h"
#include "Swiat.h"
using namespace std;

Lis::Lis(Swiat* swiat, int x, int y) : Zwierze(swiat, 3, 7, x, y, "Lis") {}
char Lis::rysowanie() const {
    return 'L';
}
Organizm* Lis::klonuj(Swiat* swiat, int x, int y) const {
    return new Lis(swiat, x, y);
}
void Lis::akcja() {
    wiekInkrementacja();

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };
    int kierunki[4] = {0, 1, 2, 3};

    // Tasowanie kierunków
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(kierunki[i], kierunki[j]);
    }

    Swiat* swiat = getSwiat();

    for (int i = 0; i < 4; i++) {
        int k = kierunki[i];
        int oldX = getX();
        int oldY = getY();
        int newX = oldX + dx[k];
        int newY = oldY + dy[k];

        if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
            Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);

            if (cel == nullptr) {
                swiat->dodajLog("Lis przeszedl na pole (" + to_string(newX) + "," + to_string(newY) + ")");
                setPozycja(newX, newY);
                return;
            } else if (cel->getSila() <= getSila()) {
                swiat->dodajLog("Lis ruszyl na pole (" + to_string(newX) + "," + to_string(newY) + ") gdzie stoi " + cel->getNazwa());
                kolizja(cel, oldX, oldY);
                return;
            } else {
                swiat->dodajLog("Lis unika silniejszego organizmu " + string(cel->getNazwa()) + " na (" + to_string(newX) + "," + to_string(newY) + ")");
            }
        }
    }

    swiat->dodajLog("Lis nie znalazl bezpiecznego pola do ruchu.");
}
