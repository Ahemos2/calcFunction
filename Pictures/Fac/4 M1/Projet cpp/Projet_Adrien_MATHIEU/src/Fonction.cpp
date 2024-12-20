#include "Fonction.h"

ostream& operator<<(ostream& os, const Fonction& f){
    return os<<f.nom<<" = "<<f.affiche();
};
ostream& operator<<(ostream& os, const Fonction* f){
    return os<<f->nom<<" = "<<f->affiche();
};

bool Fonction::isValidInteger(const string& str) const{
    stringstream ss(str);
    double d;
    ss >> d;
    return ss.eof() && !ss.fail();
}



