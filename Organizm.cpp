#include <iostream>
#include "Organizm.h"
#include "Swiat.h"
using namespace std;

Organizm::Organizm(Swiat* swiat, int sila, int inicjatywa, int x, int y)
    : swiat(swiat), sila(sila), inicjatywa(inicjatywa), x(x), y(y) {}
Organizm::~Organizm() {}
int Organizm::getSila() const {
    return sila;
}
int Organizm::getInicjatywa() const {
    return inicjatywa;
}
int Organizm::getX() const {
    return x;
}
int Organizm::getY() const {
    return y;
}
int Organizm::getWiek() const {
    return wiek;
}
Swiat* Organizm::getSwiat() const {
    return swiat;
}
bool Organizm::czyZywy() const {
    return zywy;
}
void Organizm::setSila(int sila) {
    this->sila = sila;
}
void Organizm::setPozycja(int newX, int newY) {
    x = newX;
    y = newY;
}
void Organizm::wiekInkrementacja() {
    wiek++;
}
void Organizm::zabij() {
    zywy = false;
}
