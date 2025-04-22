#include "Mlecz.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

Mlecz::Mlecz(Swiat* swiat, int x, int y)
    : Roslina(swiat, 0, x, y) {}
char Mlecz::rysowanie() const {
    return 'M';
}
Organizm* Mlecz::klonuj(Swiat* swiat, int x, int y) const {
    return new Mlecz(swiat, x, y);
}
void Mlecz::akcja() {
    wiekInkrementacja();
    for(int i = 0; i < 3; i++) {
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
                getSwiat()->dodajLog("Mlecz rozsial sie na (" + to_string(newX) + "," + to_string(newY) + ")");
                return;
            }
        }
    }
}