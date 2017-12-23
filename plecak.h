/*
Kod do wykorzystania przez studentow w ramach zajec z przedmiotu
Algorytmy i struktury danych

autor: Ewa Figielska
*/

//Oznaczenia:
//n = liczba projektow
//b = dostepny budzet
//c = zysk  (tablica n+1 elementowa)
//a = naklady(tablica n+1 elementowa)
//wartosci w tablicach a i c (zysk i naklady) sa zapisane od pozycji o indeksie 1

#ifndef _PLECAK
#define _PLECAK

typedef unsigned int UI;
const UI BARDZO_DUZA = 	4294967295; 
UI plecakAlgProgDynamicznego(UI liczbaProjektow,UI dostepnyBudzet,UI*zyski,UI*naklady);
UI plecakGenerowaniePodzbiorow(UI liczbaProjektow,UI dostepnyBudzet,UI*zyski,UI*naklady);
//dla algorymu zachlannego
struct Element{
	UI numer; //numer projektu
	double wartosc; //wartosc ilorazu zysk/naklady   
};
int porownaj(const void *x,const void* y);
UI plecakAlgZachlanny(UI n,UI b,UI*c,UI*a);

#endif