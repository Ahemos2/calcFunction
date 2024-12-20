#ifndef PUISSANCE_H
#define PUISSANCE_H

#include <Fonction.h>
#include <cmath>


class Puissance : public Fonction{
    protected:
        Fonction* pF1;
        double n;
        string affiche() const override;

    public:
        Puissance() = delete;
        Puissance(string _nom,Fonction* _pF1,double _n):Fonction(_nom),pF1{_pF1},n{_n}{};
        virtual ~Puissance() = default;
        Puissance(const Puissance& other) = default;
        Puissance& operator=(const Puissance& other) = default;

        double eval(double) const;
        Fonction* derive();

};

#endif // PUISSANCE_H
