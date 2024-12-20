#include "Polynome.h"
#include <cmath>

Polynome::Polynome(string _nom,vector<double> _coefficients): // construction
    Fonction(_nom){
        /* // si Polynome <1,0,0,0,0>, ne garder que <1>
    bool test{};
    for(int i{_coefficients.size()-1}; i>=0; i--){
        if(!test&&coefficients[i]!=0)
            test = true;
        if(test)
            coefficients.insert(0,1,_coefficients[i]);
    }
    */
    coefficients=_coefficients;
}


string Polynome::affiche() const{
    ostringstream ss;

    for (size_t i = 0; i < coefficients.size(); ++i) {
        double coef = coefficients[i];

        // Ignorer les termes avec coefficient 0
        if (coef == 0) continue;

        // Ajouter le signe + ou - (mais pas pour le premier terme positif)
        if (!ss.str().empty()) {
            ss << (coef > 0 ? "+" : "-");
        } else if (coef < 0) {
            ss << "-";
        }

        // Ajouter le coefficient (valeur absolue si déjà traité le signe)
        if (fabs(coef) != 1 || i == 0) {
            ss << fixed << affiche_reel(fabs(coef));
        }

        // Ajouter la variable et l'exposant (si degré >= 1)
        if (i > 0) {
            ss << "x";
            if (i > 1) {
                ss << "^" << i;
            }
        }
    }

    // Si tous les coefficients sont nuls, afficher simplement 0
    if (ss.str().empty()) {
        return "0";
    }

    return ss.str();
}


double Polynome::eval(double x) const{
    double res{0},puis{1};
    for(int i{0}; i<coefficients.size(); i++){
        for(int j{0}; j<i;j++)
            puis = puis * x;
        res += coefficients[i] * puis;
        puis = 1;
    }
    return(res);
}

Polynome* Polynome::simplifier(const Polynome* p1, const Polynome* p2) {
    size_t maxSize = std::max(p1->coefficients.size(), p2->coefficients.size());
    std::vector<double> result(maxSize, 0.0);

    for (size_t i = 0; i < p1->coefficients.size(); ++i) {
        result[i] += p1->coefficients[i];
    }
    for (size_t i = 0; i < p2->coefficients.size(); ++i) {
        result[i] += p2->coefficients[i];
    }

    return new Polynome(p1->nom,result);
}

Fonction* Polynome::derive(){
    vector<double> res;
    for(int i{1}; i<coefficients.size(); i++){
        res.push_back(coefficients[i]*i);
    }
    Fonction* pdf = new Polynome("d"+nom,res);
    return(pdf);
}











