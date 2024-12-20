#include "Interface.h"

/**
 * @brief Macros de debugging conditionnel.
 *
 * Utilisez DEBUG_COUT(x) pour afficher des messages de debugging lorsque DEBUG vaut 1.
 * Exemple :
 * #define DEBUG 1
 * DEBUG_COUT("Message de d�bogage");
 */

#define DEBUG 0
#if DEBUG
    #define DEBUG_COUT(x) cout << "\033[31m" << "DEBUG: " << x << "\033[0m" << endl
#else
    #define DEBUG_COUT(x) // Ne fait rien
#endif

/**
 * @brief M�thode principale pour ex�cuter l'interface utilisateur.
 *
 * Cette m�thode g�re l'entr�e utilisateur pour ex�cuter des commandes soit � partir d'un fichier, soit en mode interactif.
 *
 * Fonctionnement :
 * - Si l'utilisateur fournit un fichier valide, les commandes sont lues depuis ce fichier.
 * - Si aucune entr�e n'est donn�e (Entr�e vide), le mode interactif est lanc�.
 * - Les lignes de commandes pr�fix�es par "/" sont ignor�es, lors de la lecture des fichiers.
 * - Les lignes de commandes pr�fix�es par "#" sont pr�-�xecut�, lors de la lecture des fichiers.
 *
 * Exemple d'utilisation :
 * @code
 * Interface interface;
 * interface.run();
 * @endcode
 */

void Interface::run(){
    string input;
    string nomFichier;
    bool fichierValide = false;

    // R�p�ter jusqu'� ce qu'un fichier valide soit fourni ou que l'utilisateur appuie sur Entr�e
    while (!fichierValide) {
        cout << "Entrez le nom du fichier (ou appuyez sur Entree pour le mode interactif) : ";
        getline(cin, nomFichier);

        if (nomFichier.empty()) {
            // Mode interactif
            fichierValide = true;
        } else {
            // V�rification du fichier
            ifstream fichier(nomFichier);
            if (fichier.is_open()) {
                fichierValide = true;
                fichier.close();
            } else {
                cerr << "Erreur : Impossible d\'ouvrir le fichier \"" << nomFichier << "\". Reessayez." << endl;
            }
        }
    }

    if (!nomFichier.empty()) {
        // Lecture des commandes depuis un fichier
        ifstream fichier(nomFichier);
        while (getline(fichier, input)) {
            if (input.size()==2 && input.front() == '#' &&
                (input[1] == '0' || input[1] == '1' || input[1] == '2')) {
                isShow = input[1] - '0'; // Conversion parceque (int)'1'=49,(int)'0'=48, donc '0'-'0'=0, '1'-'0'=1
            }
            if(isShow == 1)
                cout<<">>> "<<input<<endl;
            if(isShow == 2)
                cout<<"\033[032m"<<input<<"\033[0m"<<endl;
            if (!input.empty() && input.front() != '/' && input.front() != '#') {
                executerCommande(input);
            }

        }
        fichier.close();
    } else {
        // Mode interactif
        while (true) {
            cout << ">>> ";
            getline(cin, input);
            if (input == "exit") {
                break;
            }
            executerCommande(input);
        }
    }
}

/**
 * @brief Ex�cute une commande donn�e par l'utilisateur.
 *
 * Cette fonction traite une commande sous forme de cha�ne de caract�res et ex�cute les actions correspondantes.
 * Elle g�re des commandes telles que l'aide, la liste des fonctions, ou des op�rations sur les variables.
 *
 * @param input La commande � ex�cuter sous forme de cha�ne de caract�res.
 * @return Un entier indiquant l'�tat de l'ex�cution (1 si la commande a �t� ex�cut�e avec succ�s).
 *
 * Commandes reconnues :
 * - `help` ou `?` : Affiche l'aide pour une commande sp�cifique ou g�n�rale.
 * - `liste` : Affiche la liste des fonctions disponibles.
 * - `<nom>` : Affiche une fonction pr�alablement cr��e.
 * - `<nom> = ...` ou `<nom> <- ...` : D�finit ou red�finit une fonction.
 *
 */

int Interface::executerCommande(const string& input){
    // s�paration de l'input en un vector de string
    istringstream iss(input);
    string word;
    vector<string> words;
    while (iss >> word) {
        words.push_back(word);
    }

    DEBUG_COUT("nb mots : "<<words.size());

    // si l'input est vide
    if (words.empty())
        return 1;

    // recherche si la variable existe d�ja
    string nom = words[0];
    index = findFt(nom);
    DEBUG_COUT("Index = " << index);

    // help / ?
    if(words[0].front() == '?'){ // ?
        if(words.size()==1){
            DEBUG_COUT("help : "<<words[0].substr(1));
            help(words[0].substr(1));
            return 1;
        }
        if(words.size()==2 && words[0] == "?"){
            DEBUG_COUT("help : "<<words[1]);
            help(words[1]);
            return 1;
        }
        else{
            cout<<"help : Commande non reconnue"<<endl;
            return 1;
        }
    } // endif ?
    if(words[0] == "help"){ // help
        if(words.size()==1){
            DEBUG_COUT("help");
            help("");
            return 1;
        }
        if(words.size()==2){
            DEBUG_COUT("help : "<<words[1]);
            help(words[1]);
            return 1;
        }
        else{
            cout<<"help : Commande non reconnue"<<endl;
            return 1;
        }
    } // endif help
    if(words[0] == "liste"){ // liste
        if(words.size()==1){
            liste();
            return 1;
        } else{
            cout<<"Commande non reconnue, syntaxe : liste"<<endl;
            return 1;
        }
    } // endif help

    // check si le nom n'est pas autoris�
    bool nomValide = (find(nomsInterdits.begin(), nomsInterdits.end(), words[0]) == nomsInterdits.end()) &&
                     (find(CFs.begin(), CFs.end(), words[0]) == CFs.end());
    if(nomValide)
        DEBUG_COUT("nom valide : "<<words[0]);
    else
        DEBUG_COUT("nom interdit : "<<words[0]);

    // Afficher une fonction cr��e
    if (words.size() == 1 && nomValide) {
        if (index != -1) {
            cout << pFt[index] << endl;
        } else {
            cout << "Fonction \"" << nom << "\" non definie" << endl;
        }
        return 1;
    }

    // cas default
    Fonction* fUse = use(words);
    if(fUse != nullptr){
        if (words[1] == "=" || words[1] == "<-") {
            if (index == -1) { // d�finition si nouveau nom
                pFt.push_back(fUse);
                nomFt.push_back(nom);
            } else { // red�finition si nom pr�existant
                pFt[index] = fUse;
            }
            return 1;
        } else {
            // Cas o� il n'y a pas de signe "=" ou "<-"
            cout << fUse << endl;
            delete fUse;
            return 1;
        }

    return 1;
    }
} // executerCommande

/**
 * @brief Recherche l'index d'une fonction existante par son nom.
 *
 * Cette m�thode cherche dans le vecteur `nomFt` le nom sp�cifi� et retourne son index.
 * Si le nom n'est pas trouv�, la m�thode retourne -1.
 *
 * @param nom Le nom de la fonction � rechercher.
 * @return L'index de la fonction si elle est trouv�e, sinon -1.
 *
 * Exemple d'utilisation :
 * @code
 * int index = interface.findFt("nomFonction");
 * if (index != -1) {
 *     cout << "Fonction trouv�e � l'index : " << index << endl;
 * } else {
 *     cout << "Fonction non trouv�e." << endl;
 * }
 * @endcode
 */

int Interface::findFt(string& nom)const{
    auto it = find(nomFt.begin(), nomFt.end(), nom);
    if(it != nomFt.end()){
        int index = distance(nomFt.begin(), it);
        return index;
    }
    return -1;
}

/**
 * @brief Affiche l'aide pour une commande ou pour l'ensemble des fonctionnalit�s.
 *
 * Cette m�thode fournit des explications sur l'utilisation des commandes disponibles dans le programme.
 * Si une commande sp�cifique est fournie, elle affiche l'aide associ�e � cette commande.
 * Si aucune commande n'est sp�cifi�e, elle affiche une aide g�n�rale et les commandes disponibles.
 *
 * @param commande Le nom de la commande pour laquelle afficher l'aide. Si vide, affiche une aide g�n�rale.
 *
 * Fonctionnalit�s principales document�es :
 * - `exit` : Quitter le programme.
 * - `help` ou `?` : Afficher l'aide.
 * - `liste` : Afficher les fonctions d�finies par l'utilisateur.
 * - Cr�ation de fonctions (e.g., `poly`, `composee`, `produit`).
 * - �valuation et op�rations math�matiques (e.g., `eval`, `derive`).
 * - Liste des fonctions import�es depuis CMath.
 *
 */

void Interface::help(string commande) const {
    if (commande.empty()) {
        cout << "Ce programme est une calculatrice fonctionnelle," << endl;
        help("exit");
        help("help");
        help("liste");

        cout << endl << "les fonctions prisent en compte sont : " << endl << endl;
        help("poly");
        help("composee");
        help("difference");
        help("produit");
        help("puissance");
        help("quotient");
        help("somme");
        cout<<endl;
        help("eval");
        help("derive");

        cout << "\nFonctions importees de CMath : " << endl;
        for (auto cFonction : CFs) {
            cout << cFonction;
            if (cFonction != CFs.back())
                cout << ",";
        }
        cout << endl;
    } else if (commande == "exit") {
        cout << "exit :\t\tQuitter le programme." << endl;
    } else if (commande == "help" || commande == "?") {
        cout << "? ou help :\tAfficher cette aide." << endl;
    } else if (commande == "liste") {
        cout << "liste :\t\tAffiche la liste des fonctions crees." << endl;
    } else if (commande == "poly") {
        cout << "poly :\t\tCree un polynome avec les coefficients donnes apres cette commande. \tEx: poly 1 2" << endl;
    } else if (commande == "composee") {
        cout << "composee :\tCree une fonction composee de deux fonctions existantes.\t\tEx: composee x y" << endl;
    } else if (commande == "difference") {
        cout << "difference :\tCree une fonction representant la difference entre deux fonctions.\tEx: difference x y" << endl;
    } else if (commande == "produit") {
        cout << "produit :\tCree une fonction representant le produit de deux fonctions.\t\tEx: produit x y" << endl;
    } else if (commande == "puissance") {
        cout << "puissance :\tCree une fonction representant une fonction elevee a une puissance.\tEx: puissance x 2" << endl;
    } else if (commande == "quotient") {
        cout << "quotient :\tCree une fonction representant le quotient de deux fonctions.\t\tEx: quotient x y" << endl;
    } else if (commande == "somme") {
        cout << "somme :\t\tCree une fonction representant la somme de deux fonctions.\t\tEx: somme x y" << endl;
    } else if (commande == "eval") {
        cout << "eval :\t\tEvalue une fonction en une valeure donnee.\t\t\t\tEx: eval f 3" << endl;
    } else if (commande == "derive") {
        cout << "derive :\tCree une fonction representant la derive d\'une fonction.\t\tEx: derive f" << endl;
    } else if (find(CFs.begin(), CFs.end(), commande) != CFs.end()) {
    cout << "\"" << commande << "\" : Fonction codee de CMath." << endl;
    } else {
        cout << "help : Commande non reconnue." << endl;
    }
}

/**
 * @brief �value une fonction dans le contexte de l'objet.
 *
 * Cette m�thode permet d'�valuer une fonction existante avec une valeur sp�cifi�e.
 * Si le nom de la fonction n'est pas trouv� ou si la commande est mal utilis�e, elle affiche un message d'erreur.
 *
 * @param reste Un vecteur de `string` contenant le nom de la fonction � �valuer et la valeur � �valuer.
 *
 * @return Un pointeur vers un nouvel objet `Polynome` repr�sentant le r�sultat de l'�valuation, ou nullptr en cas d'erreur.
 *
 * Fonctionnalit�s principales document�es :
 * - `eval` : �valuer une fonction avec une valeur sp�cifi�e.
 * - Si le nom de la fonction n'est pas trouv�, affiche un message d'erreur.
 * - Si la commande est mal utilis�e, affiche un message d'erreur.
 * - Retourne un nouvel objet `Polynome` contenant le r�sultat de l'�valuation.
 *
 * Exemple d'utilisation :
 * - `eval f 3` �value la fonction "f" � la valeur 3 et retourne un nouvel objet `Polynome` avec le r�sultat.
 * - Si `reste` contient uniquement "f", affiche un message d'erreur.
 * - Si la fonction "f" n'existe pas dans `pFt`, affiche un message d'erreur.
 */

Fonction* Interface::eval(const vector<string>& reste)const{
    if (reste.size() == 2) { // V�rification de la taille de reste
        DEBUG_COUT("eval : " << reste[0] << " en : " << reste[1]);
        string nom = reste[0];
        int indexEval = findFt(nom); // Recherche de la fonction entr�e
        if (indexEval == -1) {
            cout << "La fonction \"" << nom << "\" a evaluer n'existe pas." << endl;
            return nullptr;
        } else {
            try {
                double x = stod(reste[1]); // Conversion de reste[1] en double
                double result = pFt[indexEval]->eval(x); // �valuation de la fonction
                return new Polynome(reste[0], vector<double>{result});
            } catch (const std::invalid_argument&) {
                cout << "\"" << reste[1] << "\" n'est pas un nombre valide pour l'evaluation." << endl;
                return nullptr;
            } catch (const std::out_of_range&) {
                cout << "\"" << reste[1] << "\" est hors de la plage des nombres valides." << endl;
                return nullptr;
            }
        }
    } else {
        cout << "Mauvaise utilisation de eval. Exemple : eval f 3" << endl;
        return nullptr;
    }
};

/**
 * @brief Effectue la d�riv�e d'une fonction existante dans le contexte de l'objet.
 *
 * Cette m�thode permet de d�river une fonction existante. Si le nom de la fonction n'est pas trouv� ou si la commande est mal utilis�e, elle affiche un message d'erreur.
 *
 * @param reste Un vecteur de `string` contenant le nom de la fonction � d�river.
 *
 * @return Un pointeur vers un nouvel objet `Fonction` repr�sentant la fonction d�riv�e, ou nullptr en cas d'erreur.
 *
 * Fonctionnalit�s principales document�es :
 * - `derive` : D�river une fonction existante.
 * - Si le nom de la fonction n'est pas trouv�, affiche un message d'erreur.
 * - Si la commande est mal utilis�e, affiche un message d'erreur.
 * - Retourne un nouvel objet `Fonction` repr�sentant la fonction d�riv�e.
 *
 * Exemples :
 * - `derive f` d�rive la fonction "f" et retourne un nouvel objet `Fonction` de la d�riv�e.
 * - Si `reste` contient uniquement "f", affiche un message d'erreur.
 * - Si la fonction "f" n'existe pas dans `pFt`, affiche un message d'erreur.
 */

Fonction* Interface::derive(const vector<string>& reste)const{
    if(reste.size()==1){ // verification de la taille de reste
        DEBUG_COUT("derive : "<<reste[0]);
        string nom = reste[0];
        int indexEval = findFt(nom); // recherche de la fonction entr�e
        if(indexEval  == -1){
            cout<<"La fonction \""<<nom<<"\" a deriver n'existe pas"<<endl;
            return nullptr;
        } else{
            return pFt[indexEval]->derive();
        }
    }
    else{
        cout<<"Mauvaise utilisation de eval. Ex : eval f 3"<<endl;
        return nullptr;
    }
};

/**
 * @brief Affiche la liste des fonctions d�finies dans le contexte de l'objet.
 *
 * Cette m�thode permet d'afficher toutes les fonctions actuellement enregistr�es dans l'objet.
 *
 * Fonctionnalit�s principales document�es :
 * - Afficher toutes les fonctions d�finies.
 * - Si aucune fonction n'est enregistr�e, affiche "Aucune fonction enregistr�e".
 *
 */

void Interface::liste()const{
    if(pFt.size()>=1){
        for(int i{0}; i < pFt.size(); ++i){
            DEBUG_COUT("liste : "<<i);
            cout << pFt[i] << endl;
        }
    } else {
        cout << "Aucune fonction enregistre" << endl;
    }
}

/**
 * @brief Utilise et traite une commande pour cr�er une fonction ou effectuer une op�ration.
 *
 * Cette m�thode analyse une commande donn�e sous forme de vecteur de `string` pour d�terminer quelle action effectuer.
 * La commande peut �tre l'ajout d'une fonction, la d�rivation, l'�valuation, ou d'autres op�rations sur les fonctions existantes.
 *
 * @param words Un vecteur de `string` contenant la commande � traiter.
 *
 * @return Un pointeur vers un nouvel objet `Fonction` repr�sentant le r�sultat de la commande, ou nullptr en cas d'erreur.
 *
 * Fonctionnalit�s principales document�es :
 * - `use` : Analyser et ex�cuter une commande.
 * - Cr�ation de nouvelles fonctions (e.g., `poly`, `composee`, `produit`, `somme`, `quotient`, `puissance`).
 * - �valuation d'une fonction (`eval`).
 * - D�rivation d'une fonction (`derive`).
 * - Si la fonction n'est pas reconnue, affiche un message d'erreur.
 *
 * Exemples :
 * - `poly 1 2 3` cr�e une nouvelle fonction Polynome avec les coefficients donn�s.
 * - `composee f g` compose deux fonctions existantes "f" et "g" et retourne une nouvelle fonction Composee.
 * - `derive f` d�rive la fonction "f" et retourne la fonction d�riv�e.
 * - `eval f 3` �value la fonction "f" � la valeur 3 et retourne le r�sultat.
 * - `fonction_non_existante` affiche un message d'erreur pour une fonction non reconnue.
 */

Fonction* Interface::use(const vector<string>& words){
    DEBUG_COUT("use : "<<words[0]);
    string nom = words[0];
    string nomFonction;
    vector<string> reste;

    // V�rifier que le deuxi�me mot est "=" ou "<-"
    if (words.size() > 1 && (words[1] == "=" || words[1] == "<-")) {
        // D�finir `nomFonction` comme le mot suivant le signe "=" ou "<-"
        if (words.size() > 2) {
            nomFonction = words[2];
            reste = vector<string>(words.begin() + 3, words.end());
        } else {
            nomFonction = "";
            reste = {}; // Pas de reste si rien apr�s le signe "=" ou "<-"
        }
    } else {
        // Si le deuxi�me mot n'est pas "=" ou "<-", tout le reste apr�s `nom` est consid�r�
        if (words.size() > 1) {
            nomFonction = words[0];
            reste = vector<string>(words.begin() + 1, words.end());
        } else {
            nomFonction = "";
            reste = {}; // Aucun mot suivant
        }
    }
    if(nomFonction == ""){ // cas "y ="
        cout<<"Fonction non renseignee"<<endl;
        return nullptr;
    }

    if (nomFonction == "poly") {
        DEBUG_COUT("if : poly");
        vector<double> coefs;
        for (const auto& str : reste) {
            try {
                coefs.push_back(stoi(str));
            } catch (const std::invalid_argument&) {
                cout<<"\""<<str<<"\" n'est pas reconnu en tant que parametre de poly"<<endl;
                return nullptr; // Si la conversion �choue, renvoyer nullptr
            }
        }
        return new Polynome(nom, coefs);
    }
    if (nomFonction == "composee") {
        DEBUG_COUT("if : composee");
        vector<Fonction*> ft;
        if (reste.size() == 2) {
            for (auto& str : reste) {
                int index = findFt(str);
                if (index == -1) {
                    cout << "\"" << str << "\" n'est pas une fonction enregistree." << endl;
                    return nullptr; // Si la fonction n'est pas enregistr�e, renvoyer nullptr
                }
                DEBUG_COUT("Adding function: " + str);
                ft.push_back(pFt[index]);
            }
            return new Composee(nom, ft[0], ft[1]);
        }
        cout << "Cette fonction prend 2 arguments." << endl;
        return nullptr;
    }
    if (nomFonction == "difference") {
        DEBUG_COUT("if : difference");
        vector<Fonction*> ft;
        if (reste.size() == 2) {
            for (auto& str : reste) {
                int index = findFt(str);
                if (index == -1) {
                    cout << "\"" << str << "\" n'est pas une fonction enregistree." << endl;
                    return nullptr; // Si la fonction n'est pas enregistr�e, renvoyer nullptr
                }
                DEBUG_COUT("Adding function: " + str);
                ft.push_back(pFt[index]);
            }
            return new Difference(nom, ft[0], ft[1]);
        }
        cout << "Cette fonction prend 2 arguments." << endl;
        return nullptr;
    }
    if (nomFonction == "produit") {
        DEBUG_COUT("if : produit");
        vector<Fonction*> ft;
        if (reste.size() == 2) {
            for (auto& str : reste) {
                int index = findFt(str);
                if (index == -1) {
                    cout << "\"" << str << "\" n'est pas une fonction enregistree." << endl;
                    return nullptr; // Si la fonction n'est pas enregistr�e, renvoyer nullptr
                }
                DEBUG_COUT("Adding function: " + str);
                ft.push_back(pFt[index]);
            }
            return new Produit(nom, ft[0], ft[1]);
        }
        cout << "Cette fonction prend 2 arguments." << endl;
        return nullptr;
    }
    if (nomFonction == "puissance") {
        DEBUG_COUT("if : puissance");
        if (reste.size() == 2) {
            DEBUG_COUT("Creating Puissance with: f = " + reste[0] + ", n = " + reste[1]);

            // V�rifier que la fonction est enregistr�e
            Fonction* f = pFt[findFt(reste[0])];
            if (!f) {
                cout << "\"" << reste[0] << "\" n'est pas une fonction enregistree." << endl;
                return nullptr;
            }

            // Convertir l'exposant et v�rifier que c'est une valeur num�rique
            try {
                int n = std::stoi(reste[1]);
                return new Puissance(nom, f, n);
            } catch (const std::invalid_argument&) {
                cout << "\"" << reste[1] << "\" n'est pas un nombre valide." << endl;
                return nullptr;
            }
        }
        cout << "Cette fonction prend 2 arguments." << endl;
        return nullptr;
    }
    if (nomFonction == "quotient") {
        DEBUG_COUT("if : quotient");
        vector<Fonction*> ft;
        if (reste.size() == 2) {
            for (auto& str : reste) {
                DEBUG_COUT("Adding function: " + str);
                int index = findFt(str);
                if (index == -1) {
                    cout << "\"" << str << "\" n'est pas une fonction enregistree." << endl;
                    return nullptr; // Si la fonction n'est pas enregistr�e, renvoyer nullptr
                }
                ft.push_back(pFt[index]);
            }
            return new Quotient(nom, ft[0], ft[1]);
        } else {
            cout << "Cette fonction prend 2 arguments." << endl;
            return nullptr;
        }
    }
    if (nomFonction == "somme") {
        DEBUG_COUT("if : somme");
        vector<Fonction*> ft;
        if (reste.size() == 2) {
            for (auto& str : reste) {
                DEBUG_COUT("Adding function: " + str);
                int index = findFt(str);
                if (index == -1) {
                    cout << "\"" << str << "\" n'est pas une fonction enregistree." << endl;
                    return nullptr; // Si la fonction n'est pas enregistr�e, renvoyer nullptr
                }
                ft.push_back(pFt[index]);
            }
            return new Somme(nom, ft[0], ft[1]);
        } else {
            cout << "Cette fonction prend 2 arguments." << endl;
            return nullptr;
        }
    }
    if (find(CFs.begin(), CFs.end(), nomFonction) != CFs.end()) { // CFonction
        if(reste.size() == 0){
            DEBUG_COUT("if : CFonction");
            return new CFonction(nom, nomFonction);
        }
        else{
            cout << "Cette fonction ne prend pas d'arguments." << endl;
            return nullptr;
        }
    }
    if (nomFonction == "eval") {
        DEBUG_COUT("if : eval");
        return eval(reste);
    }
    if (nomFonction == "derive") {
        DEBUG_COUT("if : dervive");
        return derive(reste);
    }
    else{
        cout<<"\""<<nomFonction<<"\": fonction non reconnue"<<endl;
        return nullptr;
    }
}
