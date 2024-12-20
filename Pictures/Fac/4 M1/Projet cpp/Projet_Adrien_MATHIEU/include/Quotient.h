#ifndef QUOTIENT_H
#define QUOTIENT_H

#include <Fonction.h>


class Quotient : public Fonction{
    protected:
        Fonction* pF1;
        Fonction* pF2;
        string affiche() const override;

    public:
        Quotient() = delete;
        Quotient(string _nom,Fonction* _pF1,Fonction* _pF2):Fonction(_nom),pF1{_pF1},pF2{_pF2}{};
        virtual ~Quotient() = default;
        Quotient(const Quotient& other) = default;
        Quotient& operator=(const Quotient& other) = default;

        double eval(double) const;
        Fonction* derive();

};

#endif // QUOTIENT_H
