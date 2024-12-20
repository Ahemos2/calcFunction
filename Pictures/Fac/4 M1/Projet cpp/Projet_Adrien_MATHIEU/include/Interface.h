#ifndef INTERFACE_H
#define INTERFACE_H

#include<iostream>
#include <algorithm>
#include <fstream>

#include "Fonction.h"
#include "Polynome.h"
#include "CFonction.h"
#include "Somme.h"
#include "Difference.h"
#include "Produit.h"
#include "Quotient.h"
#include "Puissance.h"
#include "Composee.h"
using namespace std;

class Interface{
    private:
        string input;
        vector<Fonction*> pFt;
        vector<string> nomFt;
        int index;
        int isShow{0};
        vector<string> CFs{"sin","cos","tan","exp","log"}; // Fonctions codés dans CFontions
        vector<string> nomsInterdits{"exit","somme","produit","quotient",
        "composee","poly","puissance","difference","?","eval","derive","liste"}; // Noms de fonctions interdites

        int executerCommande(const string&);
        Fonction* use(const vector<string>&);
        int findFt(string&)const;
        void help(string)const;
        Fonction* eval(const vector<string>&)const;
        Fonction* derive(const vector<string>&)const;
        void liste()const;
    public:
        void run();

};

#endif // INTERFACE_H
