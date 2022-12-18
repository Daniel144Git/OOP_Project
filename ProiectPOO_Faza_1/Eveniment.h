#pragma once
#include <iostream>
#include <string>
#include "Zona.h"
#pragma warning(disable:4996)
using namespace std;

class Eveniment
{
private:
    string categorie;
    string denumire;
    int nrElementeData;
    int* data;
    Zona zona;
public:

    // constructori
    Eveniment() {
        this->categorie = "";
        this->denumire = "";
        this->data = nullptr;
    }
    Eveniment(string categorie, string denumire, int nrElementeData, int* data) : Eveniment() {
        if (categorie == "film" || categorie == "teatru" || categorie == "fotbal") {
            this->categorie = categorie;
        }
        this->denumire = denumire;
        if (nrElementeData > 0 && data != nullptr) {
            this->nrElementeData = nrElementeData;
            this->data = new int[nrElementeData];
            for (int i = 0; i < nrElementeData; i++) {
                this->data[i] = data[i];
            }
        }
    }
    Eveniment(string categorie, string denumire, int nrElementeData, int* data, Zona zona) : Eveniment(categorie, denumire, nrElementeData, data) {
        this->zona = zona;
    }
    Eveniment(const Eveniment& e) : Eveniment() {
        if (e.categorie == "film" || e.categorie == "teatru" || e.categorie == "fotbal") {
            this->categorie = e.categorie;
        }
        this->zona = e.zona;
        this->denumire = e.denumire;
        if (e.nrElementeData > 0 && e.data != nullptr) {
            this->nrElementeData = e.nrElementeData;
            this->data = new int[e.nrElementeData];
            for (int i = 0; i < e.nrElementeData; i++) {
                this->data[i] = e.data[i];
            }
        }
    }
    Eveniment& operator=(const Eveniment& e) {
        if (this->data != nullptr) {
            delete[] this->data;
            this->data = nullptr;
        }
        this->zona = e.zona;
        if (e.categorie == "film" || e.categorie == "teatru" || e.categorie == "fotbal") {
            this->categorie = e.categorie;
        }
        this->denumire = e.denumire;
        if (e.nrElementeData > 0 && e.data != nullptr) {
            this->nrElementeData = e.nrElementeData;
            this->data = new int[e.nrElementeData];
            for (int i = 0; i < e.nrElementeData; i++) {
                this->data[i] = e.data[i];
            }
        }
        return *this;
    }

    // getteri si setteri
    void setCategorie(string categorie) {
        this->categorie = categorie;
    }
    string getCategorie() {
        return this->categorie;
    }
    void setDenumire(string denumire) {
        this->denumire = denumire;
    }
    string getDenumire() {
        return this->denumire;
    }
    void setZona(Zona zona) {
        this->zona = zona;
    }
    Zona getZona() {
        return this->zona;
    }
    void setData(int nrElementeData, int* data) {
        if (nrElementeData > 0 && data != nullptr) {
            this->nrElementeData = nrElementeData;
            this->data = new int[nrElementeData];
            for (int i = 0; i < nrElementeData; i++) {
                this->data[i] = data[i];
            }
        }
    }
    int* getData() {
        int* dataCopy = nullptr;
        if (nrElementeData > 0 && data != nullptr) {
            dataCopy = new int[nrElementeData];
            for (int i = 0; i < nrElementeData; i++) {
                dataCopy[i] = data[i];
            }
        }
        return dataCopy;
    }
    int getNrElemente() {
        return this->nrElementeData;
    }

    // metode generice
    string encrypt(int id)
    {
        string s = "";
        for (int i = 0; i < this->categorie.length(); i++) {
            int temp = (this->categorie[i] + id);
            s += (char)temp;
        }
        for (int i = 0; i < this->denumire.length(); i++) {
            int temp = (this->denumire[i] + id);
            s += (char)temp;
        }
        s += zona.encrypt(id);
        return s;
    }

    string decrypt(string criptat, int id)
    {
        string s = "";
        for (int i = 0; i < criptat.length(); i++) {
            int temp = (criptat[i] - id);
            s += (char)temp;
        }
        return s;
    }
    void afiseazaDetalii() {
        if (categorie.length() == 0) cout << "zona nu are categorie ";
        else cout << "categorie: " << categorie;
        if (denumire.length() == 0) cout << ", zona nu are denumire" << endl;
        else cout << ", denumire: " << denumire;
        if (nrElementeData > 0 && data != nullptr) {
            cout << ", in data de " << data[0] << "." << data[1] << "." << data[2] << endl;
        }
        else cout << "Data nu este setata!" << endl;
    }
    static Eveniment* genereazaEvenimente(int& NR_EVENIMENTE) {
        NR_EVENIMENTE = 12;
        Eveniment* evenimente = new Eveniment[NR_EVENIMENTE];

        int data[] = { 16, 12, 2022 };
        int data1[] = { 17, 12, 2022 };
        int data2[] = { 18, 12, 2022 };
        int data3[] = { 23, 1, 2023 };

        evenimente[0] = Eveniment("film", "James Bond", 3, data);
        evenimente[1] = Eveniment("film", "Motanul incaltat", 3, data1),
            evenimente[2] = Eveniment("film", "Frozen II", 3, data2);
        evenimente[3] = Eveniment("film", "Capra cu trei iezi", 3, data3);
        evenimente[4] = Eveniment("teatru", "Doi pe banca", 3, data);
        evenimente[5] = Eveniment("teatru", "D'ale carnavalului", 3, data1);
        evenimente[6] = Eveniment("teatru", "O scrisoare pierduta", 3, data2);
        evenimente[7] = Eveniment("teatru", "O noapte furtunoasa", 3, data3);
        evenimente[8] = Eveniment("fotbal", "Rapid - FCSB", 3, data);
        evenimente[9] = Eveniment("fotbal", "Farul - Viitorul", 3, data1);
        evenimente[10] = Eveniment("fotbal", "Rapid - Farul", 3, data2);
        evenimente[11] = Eveniment("fotbal", "FC Craiova - Cluj", 3, data3);

        return evenimente;
    }
    // destructor
    ~Eveniment() {
        if (this->data != nullptr) {
            delete[] this->data;
            this->data = nullptr;
        }
    }

    // operatori
    bool operator==(const Eveniment& ev) {
        if (this->categorie != ev.categorie) return false;
        if (this->denumire != ev.denumire) return false;
        if (this->nrElementeData != ev.nrElementeData || this->data == nullptr || ev.data == nullptr) return false;
        for (int i = 0; i < this->nrElementeData; i++) {
            if (this->data[i] != ev.data[i]) {
                return false;
            }
        }
        return true;
    }
    int operator[](string element) {
        if (this->nrElementeData != 3 && this->data != nullptr) return 0;
        if (element != "luna" || element != "an" || element != "zi") {
            return 0;
        }
        if (element == "zi") return this->data[0];
        if (element == "luna") return this->data[1];
        if (element == "an") return this->data[2];
    }

    friend ostream& operator<<(ostream&, Eveniment);
    friend istream& operator>>(istream&, Eveniment&);
};



ostream& operator<<(ostream& os, Eveniment c) {
    if (c.categorie.length() == 0) os << "Zona nu are categorie." << endl;
    else os << "categorie: " << c.categorie << endl;
    if (c.denumire.length() == 0) os << "Zona nu are denumire." << endl;
    else os << "denumire: " << c.denumire << endl;
    if (c.nrElementeData > 0 && c.data != nullptr) {
        os << c.data[0] << "." << c.data[1] << "." << c.data[2] << endl;
    }
    else os << "Data nu este setata!" << endl;
    return os;
}
istream& operator>>(istream& is, Eveniment& c) {
    cout << "Introduceti categoria evenimentului: ";
    is >> c.categorie;
    cout << "Introduceti denumirea evenimentului: ";
    is >> c.denumire;
    int nr = 3;
    int* data = new int[nr];
    int element;
    cout << "Ziua: ";
    is >> element;
    while (element < 1 || element > 31) {
        cout << "Incorect! Ziua: ";
        is >> element;
    }
    data[0] = element;
    cout << "Luna: ";
    is >> element;
    while (element < 1 || element > 12) {
        cout << "Incorect! Luna: ";
        is >> element;
    }
    data[1] = element;
    cout << "Anul: ";
    is >> element;
    while (element < 2022 || element > 2023) {
        cout << "Incorect! Anul: ";
        is >> element;
    }
    data[2] = element;
    c.setData(3, data);
    cout << "Dati zona:";
    is >> c.zona;
    return is;
}
