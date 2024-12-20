#ifndef POLYNOME_H
#define POLYNOME_H

#include <Fonction.h>
#include<vector>

class Polynome : public Fonction{
    protected:
        string affiche() const override;
        vector<double> coefficients;

    public:
        Polynome() = delete;
        Polynome(string,vector<double>);
        virtual ~Polynome() = default;
        Polynome(const Polynome& other) = default;
        Polynome& operator=(const Polynome& other) = default;

        vector<double>& getCoefficients(){return coefficients;};
        static Polynome* simplifier(const Polynome*, const Polynome*);
        double eval(double) const;
        Fonction* derive();


};

#endif // POLYNOME_H
