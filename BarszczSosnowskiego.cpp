#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"
#include <iostream>
using namespace std;

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, int x, int y)
    : Roslina(swiat, 10, x, y) {}
char BarszczSosnowskiego::rysowanie() const {
    return 'S';
}
Organizm* BarszczSosnowskiego::klonuj(Swiat* swiat, int x, int y) const {
    return new BarszczSosnowskiego(swiat, x, y);
}
void BarszczSosnowskiego::akcja() {
    wiekInkrementacja();
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    // Usuwanie sasiednich zwierzat
    for (int i = 0; i < 4; ++i) {
        int newX = getX() + dx[i];
        int newY = getY() + dy[i];

        if (newX >= 0 && newX < getSwiat()->getSzerokosc() && newY >= 0 && newY < getSwiat()->getWysokosc()) {
            Organizm* cel = getSwiat()->getOrganizmNaPolu(newX, newY);
            if (cel != nullptr && dynamic_cast<Zwierze*>(cel) != nullptr) {
                getSwiat()->dodajLog(typeid(*this).name() + string(" zabija ") + typeid(*cel).name() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                cel->zabij();
            }
        }
    }

    // Zwykla akcja rosliny
    if(rand() % 10 == 0) {
        int kierunki[4] = {0, 1, 2, 3};
        for (int i = 3; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(kierunki[i], kierunki[j]);
        }

        for (int i = 0; i < 4; ++i) {
            int k = kierunki[i];
            int newX = getX() + dx[k];
            int newY = getY() + dy[k];

            if (newX >= 0 && newX < getSwiat()->getSzerokosc() && newY >= 0 && newY < getSwiat()->getWysokosc() && getSwiat()->getOrganizmNaPolu(newX, newY) == nullptr) {
                Organizm* nowa = klonuj(getSwiat(), newX, newY);
                getSwiat()->dodajOrganizm(nowa);
                getSwiat()->dodajLog("Barszcz Sosnowskiego rozsial sie na (" + to_string(newX) + "," + to_string(newY) + ")");
                return;
            }
        }
    }
}
void BarszczSosnowskiego::kolizja(Organizm* inny, int oldX, int oldY) {
    getSwiat()->dodajLog(typeid(*this).name() + string(" zjada ") + typeid(*inny).name() + string(" na polu (") + to_string(getX()) + "," + to_string(getY()) + ")");
    getSwiat()->dodajLog(typeid(*this).name() + string(" umiera na polu (") + to_string(getX()) + "," + to_string(getY()) + ")");
    inny->zabij();
    this->zabij();
}