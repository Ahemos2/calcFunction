#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include <Fonction.h>
#include <Polynome.h>


class Difference : public Fonction{
    protected:
        Fonction* pF1;
        Fonction* pF2;
        string affiche() const override;

    public:
        Difference() = delete;
        Difference(string _nom,Fonction* _pF1,Fonction* _pF2):Fonction(_nom),pF1{_pF1},pF2{_pF2}{};
        virtual ~Difference() = default;
        Difference(const Difference& other) = default;
        Difference& operator=(const Difference& other) = default;

        double eval(double) const;
        Fonction* derive();

};

#endif // DIFFERENCE_H
