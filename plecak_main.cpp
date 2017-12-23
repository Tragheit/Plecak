/*
Kod do wykorzystania przez studentow w ramach zajec z przedmiotu
Algorytmy i struktury danych

autor: Ewa Figielska
*/

/*
struktura plików:
plecak_main.cpp - funkcja main
plecak.h - naglowki funkcji, nazwy i definicje typow
plecak.cpp - kod zrodlowy funkcji
*/

#include<iostream>
#include<ctime>
#include "plecak.h"
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

void odpalamy(UI liczbaProjektow, UI dostepnyBudzet, ofstream& myfile);

int main() {
    std::ofstream myfile;
    myfile.open ("results.txt");

    /*
     Tablica zestawow danych -> tabelki 1 i 2
    nalezy ja uzupelnic dla algorytmow APD oraz AZ

     Przeprowadzenie eksperymentu dla algorytmu AP
    dla zestawow wiekszych niz {25, 100} nie przyniesie rezultatow
     ze wzgledu na dlugi czas wykonania (kilka dni+)
    */

    UI dane[8][2]{
            {10,    10},
            {10,    20},
            {10,    30},
            {10,    40},
            {25,    25},
            {25,    50},
            {25,    75},
            {25,    100}
            // dla algorytmow APD oraz AZ trzeba tu dopisac zestawy {2500, 2500} itd.
    };

    for (int i = 0; i < 8; i++) {
    //tutaj musi byc i < ilosc zestawow z tablicy dane
        cout <<"\n\n****************************\n";
        cout << "projekty: " << dane[i][0] << " budzet: " << dane[i][1] << endl;
        cout <<"****************************\n";

        myfile <<"\n\n****************************\n";
        myfile << "projekty: " << dane[i][0] << " budzet: " << dane[i][1] << endl;
        myfile <<"****************************\n";
           odpalamy(dane[i][0], dane[i][1], myfile);
    }
    cout << "done";

    myfile.close();
}

    void odpalamy(UI liczbaProjektow, UI dostepnyBudzet, ofstream& myfile) {
        srand(time(NULL));

        UI wynikAP, wynikAPD, wynikAZ;
        bool status;
        UI *tablicaZyskow = new UI[liczbaProjektow + 1];
        UI *tablicaNakladow = new UI[liczbaProjektow + 1];

        for (int i = 0; i < 2; i++) {
            cout << "\nZestaw " << i + 1 << ":  \n";
            myfile << "\nZestaw " << i + 1 << ":  \n";

            for (int i = 1; i < liczbaProjektow + 1; i++) {
                tablicaNakladow[i] = rand() % 10 + 1;
                tablicaZyskow[i] = rand() % 10 + 1;
            }

            //algorytm AP
            //Nalezy caly ten fragment wykomentowac dla zestawow > {25 ,100}

            status = false;
            while (!status) {
                auto startAP = std::chrono::high_resolution_clock::now();
                wynikAP = plecakGenerowaniePodzbiorow(liczbaProjektow, dostepnyBudzet, tablicaZyskow, tablicaNakladow);
                auto endAP = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> czasWykonaniaAP = endAP - startAP;

                if (czasWykonaniaAP.count()) {
                    cout << "Czas wykonania algorytmu AP: " << czasWykonaniaAP.count() << " Wartosc AP: " << wynikAP
                           << endl;

                    myfile << "Czas wykonania algorytmu AP: " << czasWykonaniaAP.count() << " Wartosc AP: " << wynikAP
                         << endl;
                    status = true;
                }
            }


            //algorytm APD
            status = false;
            while (!status) {
                auto startAPD = std::chrono::high_resolution_clock::now();
                wynikAPD = plecakAlgProgDynamicznego(liczbaProjektow, dostepnyBudzet, tablicaZyskow, tablicaNakladow);
                auto endAPD = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> czasWykonaniaAPD = endAPD - startAPD;
                if (czasWykonaniaAPD.count()) {
                    cout << "Czas wykonania algorytmu APD: " << czasWykonaniaAPD.count() << " Wartosc APD: " << wynikAPD
                           << endl;

                    myfile << "Czas wykonania algorytmu APD: " << czasWykonaniaAPD.count() << " Wartosc APD: " << wynikAPD
                         << endl;
                    status = true;
                }
            }

            //algorytm AZ
            status = false;
            while (!status) {
                auto startAZ = std::chrono::high_resolution_clock::now();
                wynikAZ = plecakAlgZachlanny(liczbaProjektow, dostepnyBudzet, tablicaZyskow, tablicaNakladow);
                auto endAZ = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> czasWykonaniaAZ = endAZ - startAZ;
                if (czasWykonaniaAZ.count()) {
                    cout << "Czas wykonania algorytmu AZ: " << czasWykonaniaAZ.count() << " Wartosc AZ: " << wynikAZ
                           << endl;

                    myfile << "Czas wykonania algorytmu AZ: " << czasWykonaniaAZ.count() << " Wartosc AZ: " << wynikAZ
                         << endl;
                    status = true;


                }
            }

            double odchylenie = 100.0 * (wynikAPD - wynikAZ) / wynikAPD;
            cout << "odchylenie: " << odchylenie << endl;

            myfile << "odchylenie: " << odchylenie << endl;


        }
    }



