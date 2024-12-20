#include "CFonction.h"
#include<typeinfo>

string CFonction::affiche() const{
    return(nomFonction);
}

CFonction::CFonction(string nom,string nomFonction):Fonction(nom),nomFonction{nomFonction}{
    if          (nomFonction == "sin")  cfonction = sin;
    else if     (nomFonction == "cos")  cfonction = cos;
    else if     (nomFonction == "tan")  cfonction = tan;
    else if     (nomFonction == "exp")  cfonction = exp;
    else if     (nomFonction == "log")  cfonction = log;
    else                                cfonction = nullptr; // fonction non supportée
}

double CFonction::eval(double x) const{
    return(cfonction(x));
}

Fonction* CFonction::derive(){
    if (nomFonction == "sin")
        return new CFonction("d"+nom,"cos",cos);
    if (nomFonction == "cos")
        return new CFonction("d"+nom,"-sin",[](double x) { return -sin(x); });
    if (nomFonction == "tan")
        return new CFonction("d"+nom,"1/(cos^2)",[](double x) { return 1 / (cos(x) * cos(x)); });
    if (nomFonction == "exp")
        return new CFonction("d"+nom,"exp",exp);
    if (nomFonction == "log")
        return new CFonction("d"+nom,"1/x",[](double x) { return 1 / x; });

    return nullptr; // autres fonctions
}
