#ifndef COMPOSEE_H
#define COMPOSEE_H

#include <Fonction.h>

class Composee : public Fonction{
    protected:
        Fonction* pF1;
        Fonction* pF2;
        string affiche() const override;

    public:
        Composee() = delete;
        Composee(string _nom,Fonction* _pF1,Fonction* _pF2):Fonction(_nom),pF1{_pF1},pF2{_pF2}{};
        virtual ~Composee() = default;
        Composee(const Composee& other) = default;
        Composee& operator=(const Composee& other) = default;

        double eval(double) const;
        Fonction* derive();

};

#endif // COMPOSEE_H
