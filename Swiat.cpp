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
void Swiat::dodajOrganizm(Organizm* nowy) {
    if (nowy->getX() >= 0 && nowy->getX() < szerokoscPlanszy && nowy->getY() >= 0 && nowy->getY() < wysokoscPlanszy) {
        noweOrganizmy.push_back(nowy);
    } else {
        delete nowy;
    }
}
void Swiat::wykonajWszystkieAkcje() {
    for (int i = 0; i < organizmy.size(); i++) {
        if (organizmy[i]->czyZywy()) {
            organizmy[i]->akcja();
        }
    }
}
void Swiat::sprawdzWszystkieKolizje() {
    for (int i = 0; i < organizmy.size(); i++) {
        for (int j = i + 1; j < organizmy.size(); j++) {
            if (organizmy[i]->getX() == organizmy[j]->getX() && organizmy[i]->getY() == organizmy[j]->getY()) {
                organizmy[i]->kolizja(organizmy[j]);
            }
        }
    }
}
void Swiat::usunWszystkieMartwe() {
    for (int i = 0; i < organizmy.size(); i++) {
        if (!organizmy[i]->czyZywy()) {
            delete organizmy[i];
            organizmy.erase(organizmy.begin() + i);
            i--;
        }
    }
}
void Swiat::sortujOrganizmy() {
    int n = organizmy.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            Organizm* a = organizmy[j];
            Organizm* b = organizmy[j + 1];

            bool zamien = false;
            if (a->getInicjatywa() < b->getInicjatywa()) {
                zamien = true;
            } else if (a->getInicjatywa() == b->getInicjatywa() && a->getWiek() < b->getWiek()) {
                zamien = true;
            }

            if (zamien) {
                Organizm* temp = organizmy[j];
                organizmy[j] = organizmy[j + 1];
                organizmy[j + 1] = temp;
            }
        }
    }
}
void Swiat::wykonajTure() {
    sortujOrganizmy();
    wykonajWszystkieAkcje();
    sprawdzWszystkieKolizje();
    usunWszystkieMartwe();

    for (Organizm* org : noweOrganizmy) {
        organizmy.push_back(org);
    }
    noweOrganizmy.clear();
    sortujOrganizmy();

}
void Swiat::rysujSwiat() const {

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
Organizm* Swiat::getOrganizmNaPolu(int x, int y) const {
    for (Organizm* org : organizmy) {
        if (org->getX() == x && org->getY() == y) {
            return org;
        }
    }
    return nullptr;
}
int Swiat::getSzerokosc() const {
    return szerokoscPlanszy;
}
int Swiat::getWysokosc() const {
    return wysokoscPlanszy;
}