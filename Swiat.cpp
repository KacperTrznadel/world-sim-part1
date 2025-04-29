#include <iostream>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Roslina.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Guarana.h"
#include "Mlecz.h"
#include "Trawa.h"
#include "WilczeJagody.h"
#include "Czlowiek.h"

using namespace std;

Swiat::Swiat(int newX, int newY): szerokoscPlanszy(newX), wysokoscPlanszy(newY), gameWin(nullptr), logWin(nullptr) {}
Swiat::~Swiat() {
    for (Organizm* org : organizmy) {
        delete org;
    }
    organizmy.clear();
    for (Organizm* org : noweOrganizmy) {
        delete org;
    }
    noweOrganizmy.clear();
    logi.clear();
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
    int logStartY = wysokoscPlanszy + 7;

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
    if (gameWin) {
        delwin(gameWin);
        gameWin = nullptr;
    }
    if (logWin) {
        delwin(logWin);
        logWin = nullptr;
    }
    endwin();
}
void Swiat::rysujSwiat() const {
    werase(gameWin);
    box(gameWin, 0, 0);

    for (Organizm* org : organizmy) {
        if(org->czyZywy()) {
            mvwaddch(gameWin, org->getY() + 1, org->getX() + 1, org->rysowanie());
        }
    }

    wrefresh(gameWin);
}
void Swiat::dodajLog(string tekst) {
    logi.push_back(tekst);
}
void Swiat::wypiszLogi(int offset) const {
    if(logi.empty()) {
        return;
    }
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
        nowy = nullptr;
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
        if (org->getX() == x && org->getY() == y && org->czyZywy()) {
            return org;
        }
    }
    for (Organizm* org : noweOrganizmy) {
        if (org->getX() == x && org->getY() == y && org->czyZywy()) {
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
void Swiat::zapiszDoPliku(string nazwaPliku) {
    ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        return;
    }

    // Zapisz wymiary świata
    plik << szerokoscPlanszy << " " << wysokoscPlanszy << endl;

    // Zapisz organizmy
    for (const Organizm* org : organizmy) {
        plik << org->getNazwa() << " " << org->getX() << " " << org->getY() << " " << org->getSila() << " " << org->getWiek() << endl;
    }

    plik << "#LOGI" << endl; // Separator dla logów
    for (string log : logi) {
        plik << log << endl;
    }

    plik.close();
}

void Swiat::wczytajZPliku(string nazwaPliku) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        return;
    }

    // Wczytaj wymiary świata
    int saveSzerokoscPlanszy, saveWysokoscPlanszy;
    plik >> saveSzerokoscPlanszy >> saveWysokoscPlanszy;

    if (saveSzerokoscPlanszy != szerokoscPlanszy || saveWysokoscPlanszy != wysokoscPlanszy) {
        dodajLog("Wymiary swiata w pliku nie zgadzaja sie z aktualnymi wymiarami swiata.");
        plik.close();
        return;
    }

    // Usuń istniejące organizmy
    for (Organizm* org : organizmy) {
        delete org;
    }
    organizmy.clear();

    // Wczytaj organizmy
    string typ;
    int x, y, sila, wiek;
    while (plik >> typ) {
        if (typ == "#LOGI") break; // Separator dla logów

        plik >> x >> y >> sila >> wiek;
        Organizm* nowy = nullptr;

        // Tworzenie odpowiedniego organizmu na podstawie typu
        if (typ == "Wilk") nowy = new Wilk(this, x, y);
        else if (typ == "Owca") nowy = new Owca(this, x, y);
        else if (typ == "Lis") nowy = new Lis(this, x, y);
        else if (typ == "Zolw") nowy = new Zolw(this, x, y);
        else if (typ == "Antylopa") nowy = new Antylopa(this, x, y);
        else if (typ == "Trawa") nowy = new Trawa(this, x, y);
        else if (typ == "Mlecz") nowy = new Mlecz(this, x, y);
        else if (typ == "Guarana") nowy = new Guarana(this, x, y);
        else if (typ == "Wilcze Jagody") nowy = new WilczeJagody(this, x, y);
        else if (typ == "Barszcz Sosnowskiego") nowy = new BarszczSosnowskiego(this, x, y);
        else if (typ == "Czlowiek") nowy = new Czlowiek(this, x, y);

        if (nowy) {
            nowy->setSila(sila);
            nowy->setWiek(wiek);
            Swiat* swiat = nowy->getSwiat();
            swiat->dodajOrganizm(nowy);
        }
    }

    // Wczytaj logi
    logi.clear();
    string linia;
    while (getline(plik, linia)) {
        if (!linia.empty()) {
            logi.push_back(linia);
        }
    }

    dodajLog("Stan swiata wczytany z pliku.");
    plik.close();
}

WINDOW* Swiat::getGameWin() const {
    return gameWin;
}
WINDOW* Swiat::getLogWin() const {
    return logWin;
}
vector<string> Swiat::getLogi() const {
    return logi;
}