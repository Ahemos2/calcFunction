#ifndef PRODUIT_H
#define PRODUIT_H

#include <Fonction.h>

class Produit : public Fonction{
    protected:
        Fonction* pF1;
        Fonction* pF2;
        string affiche() const override;

    public:
        Produit() = delete;
        Produit(string _nom,Fonction* _pF1,Fonction* _pF2):Fonction(_nom),pF1{_pF1},pF2{_pF2}{};
        virtual ~Produit() = default;
        Produit(const Produit& other) = default;
        Produit& operator=(const Produit& other) = default;

        double eval(double) const;
        Fonction* derive();

};

#endif // PRODUIT_H
