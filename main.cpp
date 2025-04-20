#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

using namespace std;

int main() {
    srand(time(nullptr));  // ziarno do rand()

    const int szerokosc = 20;
    const int wysokosc = 20;

    Swiat swiat(szerokosc, wysokosc);

    // Dodaj kilka organizmów na start (dla testów)
    swiat.dodajOrganizm(new Wilk(&swiat, 2, 2));
    swiat.dodajOrganizm(new Owca(&swiat, 5, 5));
    swiat.dodajOrganizm(new Lis(&swiat, 8, 8));
    swiat.dodajOrganizm(new Zolw(&swiat, 12, 12));
    swiat.dodajOrganizm(new Antylopa(&swiat, 10, 10));

    // Inicjalizacja ncurses (potrzebna, jeśli rysowanie świata wywołuje się tylko raz)
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Główna pętla symulacji
    while (true) {
        clear();  // czyść ekran przed rysowaniem
        swiat.rysujSwiat();
        mvprintw(wysokosc + 1, 0, "Nacisnij dowolny klawisz, aby przejsc do kolejnej tury (ESC aby wyjsc).");
        refresh();

        int ch = getch();
        if (ch == 27) break;  // ESC kończy program

        swiat.wykonajTure();
    }

    // Zakończenie ncurses
    endwin();

    return 0;
}
