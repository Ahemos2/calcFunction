#include "Somme.h"

Somme::Somme(string _nom,Fonction* _pF1,Fonction* _pF2)
    :Fonction(_nom),pF1{_pF1},pF2{_pF2}{};

string Somme::affiche() const{
    if (dynamic_cast<Polynome*>(pF1) && dynamic_cast<Polynome*>(pF2)) {
        Polynome* p1 = dynamic_cast<Polynome*>(pF1);
        Polynome* p2 = dynamic_cast<Polynome*>(pF2);

        // Obtention des coefficients
        vector<double>& coeff1 = p1->getCoefficients();
        vector<double>& coeff2 = p2->getCoefficients();

        // Calculer la taille maximale nécessaire pour les deux polynômes
        int maxSize = max(coeff1.size(), coeff2.size());
        vector<double> result(maxSize, 0.0);

        // Additionner les coefficients des deux polynômes
        for (int i = 0; i < coeff1.size(); ++i)
            result[i] += coeff1[i];
        for (int i = 0; i < coeff2.size(); ++i)
            result[i] += coeff2[i];

        // Créer un nouvel objet Polynome avec les coefficients calculés
        Fonction* temp = new Polynome("", result);
        string res = temp->getAffiche();
        delete temp;

        return res;
    }
    else{
        string res;
        res += pF1->getAffiche();
        if(res != "0")
            res += " + ";
        else res = "";
        if(pF2->getAffiche() == "0");
            res += pF2->getAffiche();

        return(res);
    }
}

double Somme::eval(double x) const{
    double res{0};
    res += pF1->eval(x);
    res += pF2->eval(x);
    return(res);
}

Fonction* Somme::derive(){
    Fonction* dF = new Somme("d"+nom, pF1->derive(), pF2->derive());
    return(dF);
};
