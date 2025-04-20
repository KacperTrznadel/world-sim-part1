#include <iostream>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include "Swiat.h"
using namespace std;

Swiat::Swiat(int newX, int newY): szerokoscPlanszy(newX), wysokoscPlanszy(newY), gameWin(nullptr), logWin(nullptr) {}
Swiat::~Swiat() {
    for (Organizm* org : organizmy) {
        delete org;
    }
    zakonczOkna();
}
void Swiat::inicjalizujOkna() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int heightTerminal, widthTerminal;
    getmaxyx(stdscr, heightTerminal, widthTerminal);

    int logHeight = 10;
    int logWidth = widthTerminal - 10;
    int logStartY = wysokoscPlanszy + 5;

    gameWin = newwin(wysokoscPlanszy + 2, szerokoscPlanszy + 2, 0, 0);
    logWin = newwin(logHeight, logWidth, logStartY, 0);

    keypad(gameWin, TRUE);
    keypad(logWin, TRUE);

    scrollok(logWin, TRUE);
    box(gameWin, 0, 0);     // Rysuj ramkę w oknie gry
    wrefresh(gameWin);
    wrefresh(logWin);
}

void Swiat::zakonczOkna() {
    if (gameWin) delwin(gameWin);
    if (logWin) delwin(logWin);
    endwin();
}
void Swiat::rysujSwiat() const {
    werase(gameWin);
    box(gameWin, 0, 0);

    for (Organizm* org : organizmy) {
        mvwaddch(gameWin, org->getY() + 1, org->getX() + 1, org->rysowanie());
    }

    wrefresh(gameWin);
}
void Swiat::dodajLog(string tekst) {
    logi.push_back(tekst);
}
void Swiat::wypiszLogi(int offset) const {
    werase(logWin);
    box(logWin, 0, 0);

    int maxLines = getmaxy(logWin) - 2;
    int start = max(0, (int)logi.size() - maxLines - offset);
    int end = min((int)logi.size(), start + maxLines);

    for (int i = start; i < end; ++i) {
        mvwprintw(logWin, i - start + 1, 1, "[LOG]%s", logi[i].c_str());
    }

    wrefresh(logWin); // Odśwież okno logów
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
    usunWszystkieMartwe();

    for (Organizm* org : noweOrganizmy) {
        organizmy.push_back(org);
    }
    noweOrganizmy.clear();
    sortujOrganizmy();

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