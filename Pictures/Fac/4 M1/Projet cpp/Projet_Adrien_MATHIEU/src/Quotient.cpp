#include "Quotient.h"
#include "Difference.h"
#include "Produit.h"
#include "Puissance.h"

string Quotient::affiche() const {
    string res{"("};

    if (pF1->getAffiche() == "0")
        return "0"; // 0/b =0
    res += pF1->getAffiche() + ") / (";

    if (pF2->getAffiche() == "0")
        return "Division par zero impossible."; // a/0 = Nan
    if (pF2->getAffiche() == "1")
        return pF1->getAffiche(); // a/1 = 1
    res += pF2->getAffiche() + ")";

    return res;
}
double Quotient::eval(double x) const{
    double res{0};
    res += pF1->eval(x);
    res /= pF2->eval(x);
    return(res);
}

Fonction* Quotient::derive(){
    Fonction* dF1 = new Produit("",pF1->derive(),pF2);
    Fonction* dF2 = new Produit("",pF1,pF2->derive());
    Fonction* dNumerateur = new Difference("", dF1, dF2);
    Fonction* dDenominateur = new Puissance("", pF2, 2);

    Fonction* dF = new Quotient("d"+nom, dNumerateur, dDenominateur);
    return(dF);
};

