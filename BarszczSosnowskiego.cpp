#include "BarszczSosnowskiego.h"
#include "Swiat.h"
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
            if (cel != nullptr && typeid(*cel) != typeid(*this)) {
                getSwiat()->dodajLog(typeid(*this).name() + string(" zabija ") + cel->getNazwa() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                cel->zabij();
            }
        }
    }

    // Zwykla akcja rosliny
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
void BarszczSosnowskiego::kolizja(Organizm* inny, int oldX, int oldY) {
    getSwiat()->dodajLog(inny->getNazwa() + " zjada Barszcz Sosnowskiego na polu (" + to_string(getX()) + "," + to_string(getY()) + ")");
    getSwiat()->dodajLog(inny->getNazwa() + " umiera na polu (" + to_string(getX()) + "," + to_string(getY()) + ")");
    inny->zabij();
    this->zabij();
}