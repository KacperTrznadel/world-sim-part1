#include "Zwierze.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

Zwierze::Zwierze(Swiat* swiat, int sila, int inicjatywa, int x, int y)
    : Organizm(swiat, sila, inicjatywa, x, y) {}

void Zwierze::akcja() {

    wiekInkrementacja();
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    int kierunki[4] = {0, 1, 2, 3};

    // Tasowanie kierunków
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(kierunki[i], kierunki[j]);
    }

    Swiat* swiat = getSwiat();

    for (int i = 0; i < 4; ++i) {
        int k = kierunki[i];

        int newX = getX() + dx[k];
        int newY = getY() + dy[k];

        int oldX = getX();
        int oldY = getY();

        if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
            Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
            if (cel == nullptr) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                setPozycja(newX, newY);
                return;
            } else {
                swiat->dodajLog(typeid(*this).name() + string(" probuje wejsc na pole zajmowane przez ") + typeid(*cel).name() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                kolizja(cel, oldX, oldY);
                return;
            }
        }
    }
}

void Zwierze::kolizja(Organizm* inny, int oldX, int oldY) {

    Swiat* swiat = getSwiat();

    // Jesli kolizja jest z roslina, przekaz jej kontrole nad kolizja
    if (dynamic_cast<Roslina*>(inny)) {
        inny->kolizja(this, oldX, oldY);
        return;
    }

    if (typeid(*this) == typeid(*inny)) {

        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; i++) {
            int newX = getX() + dx[i];
            int newY = getY() + dy[i];
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                
                Organizm* potomek = this->klonuj(swiat, newX, newY);
                swiat->dodajOrganizm(potomek);
                swiat->dodajLog(typeid(*this).name() + string(" rozmnozyl sie na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                return;
            }
        }

        return;
    }

    // Próba ataku
    if (inny->czyOdbilAtak(this)) {
        swiat->dodajLog(typeid(*this).name() + string(" zostal odepchniety z ataku przez ") + typeid(*inny).name());
        setPozycja(oldX, oldY);
        return;
    }

    swiat->dodajLog(typeid(*this).name() + string(" atakuje ") + typeid(*inny).name());

    // Zwykła walka
    if (this->getSila() >= inny->getSila()) {
        swiat->dodajLog(typeid(*this).name() + string(" zabija ") + typeid(*inny).name());
        inny->zabij();
        setPozycja(inny->getX(), inny->getY());
    } else {
        swiat->dodajLog(typeid(*this).name() + string(" zostaje zabity przez ") + typeid(*inny).name());
        this->zabij();
    }
}
