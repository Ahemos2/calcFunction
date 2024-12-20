#include "Puissance.h"
#include "Polynome.h"
#include "Produit.h"

string Puissance::affiche() const {
    if (pF1->getAffiche() == "0")
        return "0"; // 0^b = 0
    if (pF1->getAffiche() == "1")
        return "1"; // 1^b = 1
    if (n == 0)
        return "1"; // a^0 = 1
    if (n == 1)
        return pF1->getAffiche(); // a^1 = a
    string res = "(" + pF1->getAffiche() + ")^" + affiche_reel(n);
    return res;
}

double Puissance::eval(double x) const{
    double res;
    res = pF1->eval(x);
    res = pow(res,n);
    return(res);
}

Fonction* Puissance::derive(){
    Fonction* nF = new Polynome("",{n});
    Fonction* n_x_dF = new Produit("",nF,pF1->derive()); // construction de la fonction n*f'
    Fonction* F_n_Moins = new Puissance("",pF1,n); // construction de la fonction f^(n-1)

    Fonction* dF = new Produit("d"+nom,n_x_dF,F_n_Moins);
    return(dF);
};
