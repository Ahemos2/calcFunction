#ifndef SOMME_H
#define SOMME_H

#include <Fonction.h>
#include <Polynome.h>
#include <Polynome.h>

class Somme : public Fonction{
    protected:
        Fonction* pF1;
        Fonction* pF2;
        string affiche() const override;

    public:
        Somme() = delete;
        Somme(string,Fonction*,Fonction*);
        virtual ~Somme() = default;
        Somme(const Somme& other) = default;
        Somme& operator=(const Somme& other) = default;

        double eval(double) const;
        Fonction* derive();

};

#endif // SOMME_H
