/*
Kod do wykorzystania przez studentow w ramach zajec z przedmiotu
Algorytmy i struktury danych

autor: Ewa Figielska
*/

#include"plecak.h"
#include<algorithm>

using namespace std;

UI plecakGenerowaniePodzbiorow(UI liczbaProjektow, UI dostepnyBudzet, UI *zyski, UI *naklady) {
    bool *podzbior = new bool[liczbaProjektow + 1]; //ciag binarny: 1-inwestowac, 0-nie inwestowac
    for (UI i = 0; i <= liczbaProjektow; i++) podzbior[i] = 0;//inicjalizacja - nie inwestujemy w zaden projekt
    UI suma_zysku = 0, suma_nakladow = 0;//calkowity zysk i calkowite naklady dla stworzonego podzbioru
    UI tmp_zysk = 0, tmp_naklady = 0; //tymczasowe wartosci

    UI p, j, k = 0; //k =liczba dotychczas wygenerowanych podzbiorow
    do {
        //tworzenie nowego pozbioru, patrz Lipski, "Kombinatoryka dla programistow"
        if (k) {//jezeli podzbior nie jest pusty
            if (podzbior[p]) { //jezeli projekt p zostal dodany do podzbioru
                tmp_naklady += naklady[p];
                tmp_zysk += zyski[p];
            } else { // p=1, czyli projet p zostal wylaczony z pozbioru
                tmp_naklady -= +naklady[p];
                tmp_zysk -= zyski[p];
            }
            if (tmp_naklady <= dostepnyBudzet)//czy stworzony podzbior jest dopuszczalny?
                if (tmp_zysk > suma_zysku) {//czy calkowity zysk dla tego podzbioru > najwiekszego zysku znalezionego do tej pory?
                    suma_zysku = tmp_zysk;//aktualizacja calkowitego zysku
                    suma_nakladow = tmp_naklady;//aktualizacja calkowitych nakladow
                }
        }
        k++;
        p = 1;
        j = k;
        while (j % 2 == 0) {
            j = j / 2;
            p++;
        }
        if (p <= liczbaProjektow) podzbior[p] = 1 - podzbior[p];
    } while (p <= liczbaProjektow);
    delete[]podzbior;
    return suma_zysku;
}

UI plecakAlgProgDynamicznego(UI liczbaProjektow, UI dostepnyBudzet, UI *zyski, UI *naklady) {
//t - tablica maksymalnych zyskow dla wykorzystanego budzetu
//zredukowana tablicy o 2 wierszach, jako ze "na raz" pracujemy tylko
//ze stanami przed i po decyzji odnosnie projektu
    UI **t = new UI *[2];
    for (UI j = 0; j <= 1; j++)t[j] = new UI[dostepnyBudzet + 1];
//	
    for (UI i = 0; i <= dostepnyBudzet; i++)
        t[0][i] = 0;
    for (UI j = 1; j <= liczbaProjektow; j++) {      //petla po projektach
        for (UI i = 0; i <= dostepnyBudzet; i++)
            t[j % 2][i] = t[(j - 1) % 2][i]; //przepisanie poprzedniego zysku
        for (UI i = 0; i <= dostepnyBudzet - naklady[j]; i++)
            if (t[(j - 1) % 2][i] + zyski[j] > t[j % 2][i + naklady[j]])//czy realizacja projektu j zwieksza zysk?
                t[j % 2][i + naklady[j]] = t[(j - 1) % 2][i] + zyski[j];//aktualizacja maksymalnego zysku

    }
    UI zysk = t[liczbaProjektow % 2][dostepnyBudzet];
    for (UI j = 0; j <= 1; j++)delete[]t[j];
    delete[]t;
    return zysk;
}

bool operator<(const Element &x, const Element &y) {
    return (x.wartosc > y.wartosc);
}

UI plecakAlgZachlanny(UI n, UI b, UI *c, UI *a) {
    Element *lista = new Element[n + 1];//lista projektow
    for (UI i = 1; i <= n; i++) {
        lista[i].numer = i;
        lista[i].wartosc = double(c[i]) / a[i];
    }
    lista[0].numer = 0;
    lista[0].wartosc = BARDZO_DUZA;

    sort(lista, lista + n + 1);

    //wybieranie projektow do realizacji
    UI suma_zysku = 0;//calkowity zysk dla stworzonego podzbioru
    UI suma_nakladow = 0;//calkowite naklady dla stworzonego podzbioru
    for (UI i = 1; i <= n; i++)
        if (suma_nakladow + a[lista[i].numer] <= b) {//czy mozna dolaczyc projekt i ze wzgledu na budzet?
            suma_nakladow += a[lista[i].numer];//aktualizacja calkowitych naklady po dolaczeniu proj. i
            suma_zysku += c[lista[i].numer];//aktualizacja calkowitego zysku po dolaczeniu projektu i
        }
    delete[]lista;
    return suma_zysku;

}




