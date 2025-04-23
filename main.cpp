#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
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

int main() {
    srand(time(nullptr));  // ziarno do rand()

    const int szerokosc = 20;
    const int wysokosc = 20;

    Swiat swiat(szerokosc, wysokosc);
    swiat.inicjalizujOkna();
    swiat.dodajLog("Symulacja rozpoczeta.");

    // Dodaj kilka organizmów na start (dla testów)
    //swiat.dodajOrganizm(new Wilk(&swiat, 2, 2));
    //swiat.dodajOrganizm(new Owca(&swiat, 5, 5));
    //swiat.dodajOrganizm(new Lis(&swiat, 8, 8));
    //swiat.dodajOrganizm(new Zolw(&swiat, 12, 12));
    //swiat.dodajOrganizm(new Antylopa(&swiat, 10, 10));
    //swiat.dodajOrganizm(new BarszczSosnowskiego(&swiat, 15, 15));
    //swiat.dodajOrganizm(new Guarana(&swiat, 18, 18));
    //swiat.dodajOrganizm(new Mlecz(&swiat, 3, 3));
    //swiat.dodajOrganizm(new Trawa(&swiat, 4, 4));
    //swiat.dodajOrganizm(new WilczeJagody(&swiat, 6, 6));
    //swiat.dodajOrganizm(new Zolw(&swiat, 2, 4));
    //swiat.dodajOrganizm(new Owca(&swiat, 1, 6));
    //swiat.dodajOrganizm(new Owca(&swiat, 3, 2));
    //swiat.dodajOrganizm(new Zolw(&swiat, 1, 1));
    //swiat.dodajOrganizm(new Wilk(&swiat, 5, 6));
    //swiat.dodajOrganizm(new Wilk(&swiat, 6, 5));
    //swiat.dodajOrganizm(new Lis(&swiat, 5, 5));
    //swiat.dodajOrganizm(new Zolw(&swiat, 5, 4));
    //swiat.dodajOrganizm(new Wilk(&swiat, 4, 5));
    swiat.dodajOrganizm(new Antylopa(&swiat, 7, 7));
    swiat.dodajOrganizm(new Wilk(&swiat, 8, 8));
    //swiat.dodajOrganizm(new Owca(&swiat, 3, 3));
    //swiat.dodajOrganizm(new Czlowiek(&swiat, 5, 5));
    int logOffset = 0;

    // Główna pętla symulacji
    while (true) {
        swiat.rysujSwiat();
        mvprintw(wysokosc + 3, 0, "Nacisnij SPACJE, aby przejsc do kolejnej tury (ESC aby wyjsc).");
        mvprintw(wysokosc + 4, 0, "Logi: (uzyj strzalek do przewijania)");
        refresh();

        int ch = wgetch(swiat.getGameWin());
        if (ch == 27) break;
        if (ch == ' ') {
            swiat.wykonajTure();
            swiat.dodajLog("=======NOWA TURA=======");
            swiat.wypiszLogi(logOffset);
        } else if (ch == 's') {
            if (logOffset > 0) logOffset--;
            swiat.wypiszLogi(logOffset);
        } else if (ch == 'w') {
            int maxOffset = max(0, (int)swiat.getLogi().size() - (getmaxy(swiat.getLogWin()) - 2));
            if (logOffset < maxOffset) logOffset++;
            swiat.wypiszLogi(logOffset);
        }
    }

    swiat.zakonczOkna();
    return 0;
}
