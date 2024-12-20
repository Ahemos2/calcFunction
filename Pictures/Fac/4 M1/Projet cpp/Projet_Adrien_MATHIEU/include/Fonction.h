#ifndef FONCTION_H
#define FONCTION_H

#include<string>
#include<ostream>
#include <sstream>
#include <typeinfo>

using namespace std;

class Fonction{
    protected:
        string nom;
        virtual string affiche() const = 0;

    public:
        Fonction() = default;
        Fonction(string _nom):nom{_nom}{};
        virtual ~Fonction() = default;
        Fonction(const Fonction& other);
        Fonction& operator=(const Fonction& other);

        virtual double eval(double) const = 0;
        virtual Fonction* derive() = 0;

        string affiche_reel(double x) const {stringstream ss; ss<<x; return ss.str();};

        string getNom() const {return nom;};
        string getAffiche() const {return affiche();};
        bool isValidInteger(const string&) const;

        friend ostream& operator<<(ostream&, const Fonction&);
        friend ostream& operator<<(ostream&, const Fonction*);
};

#endif // FONCTION_H
