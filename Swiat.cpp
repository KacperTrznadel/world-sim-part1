#include <iostream>
#include <nucurses.h>
#include <vector>
#include "Swiat.h"
using namespace std;

Swiat::Swiat(int newX, int newY): szerokoscPlanszy(newX), wysokoscPlanszy(newY) {}
Swiat::~Swiat() {
    for (Organizm* org : organizmy) {
        delete org;
    }
}
Swiat::dodajOrganizm(Organizm* nowy) {
    if (nowy->getX() >= 0 && nowy->getX() < szerokoscPlanszy && nowy->getY() >= 0 && nowy->getY() < wysokoscPlanszy) {
        organizmy.push_back(nowy);
    } else {
        delete nowy;
    }
}
Swiat::wykonajWszystkieAkcje() {
    for (int i = 0; i < organizmy.size(); i++) {
        if (organizmy[i]->czyZywy()) {
            organizmy[i]->akcja();
        }
    }
}
Swiat::sprawdzWszystkieKolizje() {
    for (int i = 0; i < organizmy.size(); i++) {
        for (int j = i + 1; j < organizmy.size(); j++) {
            if (organizmy[i]->getX() == organizmy[j]->getX() && organizmy[i]->getY() == organizmy[j]->getY()) {
                organizmy[i]->kolizja(organizmy[j]);
            }
        }
    }
}
Swiat::usunWszystkieMartwe() {
    for (int i = 0; i < organizmy.size(); i++) {
        if (!organizmy[i]->czyZywy()) {
            delete organizmy[i];
            organizmy.erase(organizmy.begin() + i);
            i--;
        }
    }
}
Swiat::wykonajTure() {
    wykonajAkcje();
    sprawdzKolizje();
    usunMartwe();
}
Swiat::rysujSwiat() const {

    // Inicjalizacja ncurses
    initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    // Ustawienie koloru tła
    for (int i = 0; i < szerokoscPlanszy; i++) {
        for (int j = 0; j < wysokoscPlanszy; j++) {
            mvaddch(j, i, ' ');
        }
    }

    // Rysowanie organizmów
    for (Organizm* org : organizmy) {
        mvaddch(org->getY(), org->getX(), org->rysowanie());
    }

    // Odświeżenie ekranu ze zmianami - gotowe na pierwszą turę
    refresh();
}
Swiat::getOrganizmNaPolu(int x, int y) const {
    for (Organizm* org : organizmy) {
        if (org->getX() == x && org->getY() == y) {
            return org;
        }
    }
    return nullptr;
}
Swiat::getSzerokosc() const {
    return szerokoscPlanszy;
}
Swiat::getWysokosc() const {
    return wysokoscPlanszy;
}