#ifndef CFONCTION_H
#define CFONCTION_H

#include <Fonction.h>
#include <cmath>

class CFonction : public Fonction{
    private:
        double (*cfonction)(double);
        string affiche() const override;
        string nomFonction;

    public:
        CFonction() = delete;
        CFonction(string nom,string nomFonction);
        CFonction(string nom,string nomFonction,double (*cfonction)(double)):Fonction(nom),nomFonction{nomFonction},cfonction(cfonction) {};
        virtual ~CFonction() = default;
        CFonction(const CFonction& other) = default;
        CFonction& operator=(const CFonction& other) = default;

        double eval(double) const;
        Fonction* derive();
};

#endif // CFONCTION_H
