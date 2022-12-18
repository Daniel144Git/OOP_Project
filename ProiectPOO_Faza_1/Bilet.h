#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Eveniment.h"
#include "Zona.h"
#pragma warning(disable:4996)
using namespace std;

class Bilet
{
private:
    // camp privat care nu va avea getter deoarece este folosit pentru a genera bilete unice
    const int id;
    char* cod; // nu va avea setter pentru ca e generat intern
    Eveniment eveniment;
    float pret;
    string codLoc;
public:
    static int nrBilete;

    // constructori
    Bilet() :id(++nrBilete) {
        this->cod = nullptr;
        this->pret = 0;
        this->codLoc = "";
    }
    Bilet(Eveniment eveniment) : Bilet() {
        this->eveniment = eveniment;
    }
    Bilet(Eveniment eveniment, float pret, int rand, int loc) : Bilet() {
        this->eveniment = eveniment;
        if (pret > 0) {
            this->pret = pret;
        }
        this->setLocScaun(rand, loc);
        this->encrypt();
    }
    Bilet(const Bilet& bilet) : Bilet() {
        this->eveniment = bilet.eveniment;
        if (bilet.pret > 0) {
            this->pret = bilet.pret;
        }
        this->codLoc = bilet.codLoc;
        if (bilet.cod != nullptr) {
            this->cod = new char[strlen(bilet.cod) + 1];
            strcpy(this->cod, bilet.cod);
        }
    }

    // getteri si setteri
    void setEveniment(Eveniment eveniment) {
        this->eveniment = eveniment;
    }
    Eveniment getEveniment() {
        return this->eveniment;
    }
    void setPret(float pret) {
        if (pret > 0) {
            this->pret = pret;
        }
    }
    float getPret() {
        return this->pret;
    }
    string getLocScaun() {
        return this->codLoc;
    }
    void setLocScaun(int nrRand, int nrLoc) {
        this->codLoc = this->eveniment.getZona().getCodScaun(nrRand, nrLoc);
    }
    string getCod() {
        string s = "";
        if (cod != nullptr) {
            s = cod;
        }
        return s;
    }
    // metode specifice
    bool validareBilet(Eveniment eveniment, Zona zona, int loc, int rand) {
        this->encrypt();
        string codScaunCalculat = zona.getCodScaun(rand, loc);
        if (codScaunCalculat != this->codLoc) {
            cout << "Locul nu este corect!" << endl;
            return false;
        }
        string codEveniment = eveniment.encrypt(this->id) + codScaunCalculat;
        if (strcmp(this->cod, codEveniment.c_str()) != 0) {
            cout << "Biletul nu este corect! Codul biletului este " << this->cod << " si trebuia sa fie " + codEveniment << endl;
            return false;
        }
        if (this->eveniment.getData() == nullptr || this->eveniment.getNrElemente() < 3 || eveniment.getData() == nullptr || eveniment.getNrElemente() < 3) {
            cout << "Data nu este valida!" << endl;
            return false;
        }
        for (int i = 0; i < eveniment.getNrElemente(); i++) {
            if (this->eveniment.getData()[i] != eveniment.getData()[i]) {
                cout << "Data este gresita!" << endl;
                return false;
            }
        }

        return true;
    }

private:
    void encrypt()
    {
        if (this->codLoc == "") return;
        string s = this->eveniment.encrypt(this->id);
        s += this->codLoc;
        this->cod = new char[strlen(s.c_str()) + 1];
        strcpy(this->cod, s.c_str());
    }

    string decrypt()
    {
        string s = "";
        for (int i = 0; i < strlen(this->cod); i++) {
            int temp = (this->cod[i] - this->id);
            cout << (char)temp;
            s += (char)temp;
        }
        return s;
    }


public:
    // destructor
    ~Bilet() {
        --nrBilete;
        if (this->cod != nullptr) {
            delete this->cod;
            this->cod = nullptr;
        }
    }

    // operatori
    Bilet operator+ (float pret) {

        if (pret > 0) {
            this->pret += pret;
        }
        return *this;
    }
    bool operator<(const Bilet& b) {
        return this->pret < b.pret;
    }

    Bilet& operator=(const Bilet& bilet) {
        --nrBilete;
        if (this->cod != nullptr) {
            delete this->cod;
            this->cod = nullptr;
        }
        this->eveniment = bilet.eveniment;
        if (bilet.pret > 0) {
            this->pret = bilet.pret;
        }
        this->codLoc = bilet.codLoc;
        if (bilet.cod != nullptr) {
            this->cod = new char[strlen(bilet.cod) + 1];
            strcpy(this->cod, bilet.cod);
        }
        return *this;
    }

    friend ostream& operator<<(ostream&, Bilet);
    friend istream& operator>>(istream&, Bilet&);
};
int Bilet::nrBilete = 0;

ostream& operator<<(ostream& os, Bilet c) {
    if (c.cod != nullptr) os << "Cod: " << c.cod << endl;
    else os << "Biletul nu are cod!" << endl;
    os << "Pentru evenimentul: " << c.eveniment << endl;
    if (c.codLoc.length() == 4)
        os << "Locul: rand " << c.codLoc[0] << c.codLoc[1] << ", rand " << c.codLoc[2] << c.codLoc[3] << endl;
    else os << "Biletul nu are loc!" << endl;
    os << "Costa " << c.pret << " lei" << endl;
    return os;
}
istream& operator>>(istream& is, Bilet& c) {
    cout << "Introduceti evenimentul dorit: ";
    is >> c.eveniment;
    cout << "Dati pretul: ";
    is >> c.pret;
    cout << "Ce rand doriti?";
    int rand, loc = 0;
    is >> rand;
    cout << "Ce loc doriti?";
    is >> loc;
    c.setLocScaun(rand, loc);
    return is;
}
