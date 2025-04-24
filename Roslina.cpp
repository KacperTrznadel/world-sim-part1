#include <iostream>
#include "Roslina.h"
#include "Swiat.h"
#include <cstdlib>
using namespace std;

Roslina::Roslina(Swiat* swiat, int sila, int x, int y)
    : Organizm(swiat, sila, 0, x, y) {} // rośliny mają inicjatywę 0

void Roslina::akcja() {
    wiekInkrementacja();

    if (rand() % 10 == 0) {
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };

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
                getSwiat()->dodajLog(typeid(*this).name() + string(" rozsial sie na (") + to_string(newX) + "," + to_string(newY) + ")");
                return;
            }
        }
    }
}

void Roslina::kolizja(Organizm* inny, int oldX, int oldY) {
    getSwiat()->dodajLog(typeid(*inny).name() + string(" zjada ") + typeid(*this).name() + string(" na polu (") + to_string(getX()) + "," + to_string(getY()) + ")");
    inny->setPozycja(this->getX(), this->getY());
    this->zabij();
}
