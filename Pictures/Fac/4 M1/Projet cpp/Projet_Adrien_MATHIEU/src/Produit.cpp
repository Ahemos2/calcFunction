#include "Produit.h"
#include "Somme.h"

string Produit::affiche() const {
    if (dynamic_cast<Polynome*>(pF1) && dynamic_cast<Polynome*>(pF2)) {
        Polynome* p1 = dynamic_cast<Polynome*>(pF1);
        Polynome* p2 = dynamic_cast<Polynome*>(pF2);

        // Obtention des coefficients
        vector<double>& coeff1 = p1->getCoefficients();
        vector<double>& coeff2 = p2->getCoefficients();

        // Calculer la taille maximale nécessaire pour les deux polynômes
        int maxSize = coeff1.size() * coeff2.size();
        vector<double> result(maxSize, 0.0);

        // Calculer le produit des coefficients
        for (size_t i = 0; i < coeff1.size(); ++i) {
            for (size_t j = 0; j < coeff2.size(); ++j) {
                result[i + j] += coeff1[i] * coeff2[j];
            }
        }

        // Créer un nouvel objet Polynome avec les coefficients calculés
        Fonction* temp = new Polynome("", result);
        string res = temp->getAffiche();
        delete temp;

        return res;
    }
    else{
        string res{"("};

        if (pF1->getAffiche() == "0")
            return "0"; // 0*b =0
        if (pF1->getAffiche() == "1")
            return pF2->getAffiche(); // 1*b =b
        res += pF1->getAffiche() + ") * ("; // cas normal

        if (pF2->getAffiche() == "0")
            return "0"; // a*0 = 0
        if (pF2->getAffiche() == "1")
            return pF1->getAffiche(); // a*1 = 1
        res += pF2->getAffiche() + ")"; // cas normal

        return res;
    }
}

double Produit::eval(double x) const{
    double res{0};
    res += pF1->eval(x);
    res *= pF2->eval(x);
    return(res);
}

Fonction* Produit::derive(){
    Fonction* dF1 = new Produit("",pF1->derive(),pF2);
    Fonction* dF2 = new Produit("",pF1,pF2->derive());
    Fonction* dF = new Somme("d"+nom, dF1, dF2);
    return(dF);
};
