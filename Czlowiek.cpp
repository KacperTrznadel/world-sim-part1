#include "Czlowiek.h"
#include "Swiat.h"
#include <iostream>
#include <curses.h>
using namespace std;

Czlowiek::Czlowiek(Swiat* swiat, int x, int y) : Zwierze(swiat, 5, 4, x, y) {}
