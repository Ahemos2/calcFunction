#include "Composee.h"
#include "Produit.h"

string Composee::affiche() const{
    string res;
    if(pF1->getAffiche() == "0") // 0of = 0
        return "0";
    if(pF1->getAffiche() == "1") // 1of = f
        return pF2->getAffiche();
    if(isValidInteger(pF1->getAffiche())) // aof = a
        return pF1->getAffiche();
    if(isValidInteger(pF2->getAffiche())) // fob = f(b)
        return affiche_reel(eval(0));
    if(pF2->getAffiche() == "x") // fox = f(x) = f
        return pF1->getAffiche();
    if(pF1->getAffiche() == "x") // xog = g
        return pF2->getAffiche();

    return("(" + pF1->getAffiche() + ")o(" + pF2->getAffiche() + ")");
}

double Composee::eval(double x) const{
    double res;
    res = pF2->eval(x);
    res = pF1->eval(res);
    return(res);
}

Fonction* Composee::derive(){
    Fonction* d1 = new Composee("",pF1->derive(),pF2); // f1'(f2)
    Fonction* dF = new Produit("d"+nom, pF2->derive(), d1); // f2'*(f1'(f2))
    return(dF);
};
