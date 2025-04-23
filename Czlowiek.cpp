#include "Czlowiek.h"
#include "Swiat.h"
#include <iostream>
#include <curses.h>
using namespace std;

Czlowiek::Czlowiek(Swiat* swiat, int x, int y) : Zwierze(swiat, 5, 4, x, y) {}

char Czlowiek::rysowanie() const {
    return 'C';
}
Organizm* Czlowiek::klonuj(Swiat* swiat, int x, int y) const {
    return new Czlowiek(swiat, x, y);
}

void Czlowiek::akcja() {

    Swiat* swiat = getSwiat();
    //swiat->dodajLog("Wybierz kierunek ruchu czlowieka (strzałki) lub umiejetnosc - Tarcza Alzura (a):");
    wiekInkrementacja();
    int klawisz = getch();
    int oldX = getX();
    int oldY = getY();
    int newX;
    int newY;

    //Akutalizacja dzialania i cooldownu
    if(this->getDzialanieTarczy() > 0) {
        this->setDzialanieTarczy(this->getDzialanieTarczy() - 1);
    } 
    if(this->getCooldown() > 0) {
        this->setTarczaAktywna(false);
        this->setCooldown(this->getCooldown() - 1);
        swiat->dodajLog("Tarcza Alzura bedzie dostepna za " + to_string(this->getCooldown()) + " tur!");
    }
    if(this->getDzialanieTarczy() == 0 && this->czyTarczaAktywna()) {
        this->setTarczaAktywna(false); 
        this->setCooldown(5);
        swiat->dodajLog("Tarcza Alzura przestala dzialac! Ponowne uzycie bedzie mozliwe za " + to_string(this->getCooldown()) + " tur!");
    }

    switch (klawisz) {
        case KEY_UP:
            newX = oldX;
            newY = oldY - 1;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            } else if(swiat->getOrganizmNaPolu(newX, newY) != nullptr) {
                swiat->dodajLog(typeid(*this).name() + string(" probuje wejsc na pole zajmowane przez ") + typeid(*swiat->getOrganizmNaPolu(newX, newY)).name() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                kolizja(swiat->getOrganizmNaPolu(newX, newY), oldX, oldY);
            }
            break;
        case KEY_DOWN:
            newX = oldX;
            newY = oldY + 1;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            } else if(swiat->getOrganizmNaPolu(newX, newY) != nullptr) {
                swiat->dodajLog(typeid(*this).name() + string(" probuje wejsc na pole zajmowane przez ") + typeid(*swiat->getOrganizmNaPolu(newX, newY)).name() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                kolizja(swiat->getOrganizmNaPolu(newX, newY), oldX, oldY);
            }
            break;
        case KEY_LEFT:
            newX = oldX - 1;
            newY = oldY;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            } else if(swiat->getOrganizmNaPolu(newX, newY) != nullptr) {
                swiat->dodajLog(typeid(*this).name() + string(" probuje wejsc na pole zajmowane przez ") + typeid(*swiat->getOrganizmNaPolu(newX, newY)).name() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                kolizja(swiat->getOrganizmNaPolu(newX, newY), oldX, oldY);
            }
            break;
        case KEY_RIGHT:
            newX = oldX + 1;
            newY = oldY;
            if (swiat->getOrganizmNaPolu(newX, newY) == nullptr && newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
                swiat->dodajLog(typeid(*this).name() + string(" przeszedl na pole (") + to_string(newX) + "," + to_string(newY) + ")");
                this->setPozycja(newX, newY);
            } else if(swiat->getOrganizmNaPolu(newX, newY) != nullptr) {
                swiat->dodajLog(typeid(*this).name() + string(" probuje wejsc na pole zajmowane przez ") + typeid(*swiat->getOrganizmNaPolu(newX, newY)).name() + string(" na polu (") + to_string(newX) + "," + to_string(newY) + ")");
                kolizja(swiat->getOrganizmNaPolu(newX, newY), oldX, oldY);
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
    Swiat* swiat = getSwiat();
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

    if (atakujacy->getSila() > this->getSila()) {
        swiat->dodajLog(typeid(*this).name() + string(" zostal zabity przez ") + typeid(*atakujacy).name() + string(" na polu (") + to_string(oldX) + "," + to_string(oldY) + ")"); 
        this->zabij();
    } else {
        swiat->dodajLog(typeid(*this).name() + string(" pokonal ") + typeid(*atakujacy).name() + string(" na polu (") + to_string(oldX) + "," + to_string(oldY) + ")");
        atakujacy->zabij();
    }
}