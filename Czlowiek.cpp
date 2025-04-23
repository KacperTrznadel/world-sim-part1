#include "Czlowiek.h"
#include "Swiat.h"
#include <iostream>
#include <curses.h>
using namespace std;

Czlowiek::Czlowiek(Swiat* swiat, int x, int y) : Zwierze(swiat, 5, 4, x, y) {}

void Czlowiek::akcja() {
    swiat->dodajLog("Wybierz kierunek ruchu czlowieka (strzałki) lub umiejetnosc - Tarcza Alzura (a):");
    wiekInkrementacja();
    int klawisz = getch();
    int oldX = getX();
    int oldY = getY();

    switch (klawisz) {
        case KEY_UP:
            int newX = oldX;
            int newY = oldY - 1;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            }
            break;
        case KEY_DOWN:
            int newX = oldX;
            int newY = oldY + 1;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            }
            break;
        case KEY_LEFT:
            int newX = oldX - 1;
            int newY = oldY;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            }
            break;
        case KEY_RIGHT:
            int newX = oldX + 1;
            int newY = oldY;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            }
            break;
        case 'a':
            if(this->getCooldown() == 0) {
                swiat->dodajLog(typeid(*this).name() + string(" uzywa umiejetnosci Tarcza Alzura"));
                this->setTarczaAktywna(true);
                this->setDzialanieTarczy(5);
            } else {
                swiat->dodajLog("Czlowiek probuje uzyc Tarczy Alzura... ale umiejetnosc niedostepna jeszcze przez najblizsze " + to_string(getCooldown()) + " tur!");
            }
            break;
        default:
            break;
    }
}
bool Czlowiek::czyOdbilAtak(Organizm* atakujacy) {
    if(this->czyTarczaAktywna() && this->getCooldown() == 0 && this->getDzialanieTarczy() > 0) {
        swiat->dodajLog("Czlowiek odbil atak za pomoca Tarczy Alzura!");
        return true;
    } else {
        return false;
    }
}
void Czlowiek::kolizja(Organizm* atakujacy, int oldX, int oldY) {
    Swiat* swiat = getSwiat();

    //Czy tarcza aktualnie dziala - jesli tak, odbij
    if (atakujacy->czyOdbilAtak(this)) {
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };

        int kierunki[4] = {0, 1, 2, 3};

        // Tasowanie kierunków
        for (int i = 3; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(kierunki[i], kierunki[j]);
        }

        for (int i = 0; i < 4; i++) {
            int k = kierunki[i];
            int newX = atakujacy->getX() + dx[k];
            int newY = atakujacy->getY() + dy[k];
            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                atakujacy->setPozycja(newX, newY);
                swiat->dodajLog(typeid(*atakujacy).name() + string(" zostal odepchniety przez Tarcze Alzura na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                return;
            }
        }
        return;
    }

    //Akutalizacja dzialania i cooldownu
    if(this->getDzialanieTarczy() > 0) {
        this->setDzialanieTarczy(this->getDzialanieTarczy() - 1);
    } 
    if(this->getCooldown() > 0) {
        this->setTarczaAktywna(false);
        this->setCooldown(this->getCooldown() - 1);
    }
    if(this->getDzialanieTarczy() == 0 && this->czyTarczaAktywna()) {
        this->setTarczaAktywna(false); 
        this->setCooldown(5);
    }

    if (atakujacy->getSila() > this->getSila()) {
        swiat->dodajLog(typeid(*this).name() + string(" zostal zabity przez ") + typeid(*atakujacy).name() + string(" na polu (") + to_string(oldX) + "," + to_string(oldY) + ")"); 
        this->zabij();
    } else {
        swiat->dodajLog(typeid(*this).name() + string(" pokonal ") + typeid(*atakujacy).name() + string(" na polu (") + to_string(oldX) + "," + to_string(oldY) + ")");
        atakujacy->zabij();
    }
}