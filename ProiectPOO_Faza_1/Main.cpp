#include <iostream>
#include <string>
#include <ctime>
#include "Eveniment.h"
#include "Zona.h"
#include "Bilet.h"
#pragma warning(disable:4996)
using namespace std;

void afiseazaOptiuni() {
	cout << endl << "Bine ai venit!" << endl;
	cout << "Alege ce doresti:" << endl;
	cout << "1. Afiseaza evenimente disponibile si cumpara bilet." << endl;
	cout << "2. Prezinta-te la eveniment." << endl;
	cout << "3. Vizualizeaza-ti biletele" << endl;
}

Bilet cumparaBilet(Eveniment& ales, int& rand, int& loc, int NR_EVENIMENTE, Eveniment* evenimente) {
	int nrZone, alegere = 0;
	string type = "";
	while (alegere < 1 || alegere > NR_EVENIMENTE) {
		cout << "Alegeti un eveniment, sau tastati 'exit' pentru a iesi:" << endl;
		for (int i = 0; i < NR_EVENIMENTE; i++) {
			cout << (i + 1) << ". ";
			evenimente[i].afiseazaDetalii();
			cout << endl;
		}
		cout << "Decizia ta:";
		cin >> type;
		alegere = atoi(type.c_str());
	}
	ales = evenimente[((int)alegere) - 1];
	cout << endl << "Ai ales:" << endl << ales << endl;
	Zona* zone = Zona::getZonePentruEveniment(ales.getCategorie(), nrZone);
	cout << "Zonele disponibile sunt: " << endl;
	for (int i = 0; i < nrZone; i++) {
		cout << zone[i] << endl;
	}
	alegere = 0;
	while (alegere<1 || alegere > nrZone) {
		cout << "Alege o zona (numar de la 1 la " << nrZone << "):";
		cin >> type;
		alegere = atoi(type.c_str());
	}
	ales.setZona(zone[alegere - 1]);
	cout << "Ai ales: " << endl << ales.getZona() << endl;
	Bilet bilet(ales, 10 * alegere * (++rand + ++loc), rand, loc);
	cout << "Biletul tau este:" << endl << bilet << endl;
	return bilet;
}

void prezentareLaEveniment(Bilet* bilete, int nr, Eveniment eveniment, Zona zona, int rand, int loc) {
	cout << "Dati codul:";
	string cod;
	cin >> cod;
	Bilet* bilet = nullptr;
	if (bilete == nullptr || nr < 1) {
		cout << endl << "Nu ai bilete." << endl;
		return;
	}
	for (int i = 0; i < nr; i++) {
		if (bilete[i].getCod() == cod) {
			bilet = &bilete[i];
		}
	}
	if (bilet == nullptr) {
		cout << "Bilet invalid!" << endl;
		return;
	}
	bilet->validareBilet(eveniment, zona, loc, rand) ? (cout << "Bilet valid" << endl) : cout << "Bilet invalid";
}

void vizualizareBilete(Bilet* bilete, int nr) {
	if (bilete != nullptr && nr > 0) {
		for (int i = 0; i < nr; i++) {
			cout << "Bilet " << (i + 1) << ": " << endl << bilete[i] << endl;
		}
	}
	else cout << endl << "Nu ai bilete." << endl;
}

int main() {
	int NR_EVENIMENTE;
	Eveniment* evenimente = Eveniment::genereazaEvenimente(NR_EVENIMENTE);
	Bilet bilete[5];
	int nrBilete = 0;
	Bilet b;
	string type = ""; int ales = 0; int rand = 0, loc = 0; Eveniment e;
	while (type != "exit") {
		afiseazaOptiuni();
		cout << "Decizia ta:";
		cin >> type;
		ales = atoi(type.c_str());
		if (ales == 1) {
			bilete[nrBilete++] = cumparaBilet(e, rand, loc, NR_EVENIMENTE, evenimente);
		}
		else if (ales == 2) prezentareLaEveniment(bilete, nrBilete, e, e.getZona(), rand, loc);
		else if (ales == 3) vizualizareBilete(bilete, nrBilete);
	}
	return 0;
}