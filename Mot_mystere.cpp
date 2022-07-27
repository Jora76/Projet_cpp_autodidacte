// Mot_mystere.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string melange(string m);
string selectMot();
int partie();

int main()
{
    char replay('o');
    while (replay == 'o') {
        vector <string> tableauJoueurs;
        unsigned short nbJoueurs;
        cout << "Y a combien de joueurs ? :" << endl;
        cin >> nbJoueurs;
        //if(nbJoueurs
        int k(0);
        string nomJoueur;
        while(tableauJoueurs.size() < nbJoueurs){
            cout << "Joueur " << k + 1 << " quel est ton nom ? :" << endl;
            cin >> nomJoueur;
            tableauJoueurs.push_back(nomJoueur);
            ++k;
        }

        vector <int> tableauScores;
        k = 0;
        while (k < nbJoueurs) {
            cout << tableauJoueurs[k] << " a toi de jouer." << endl;
            int score = partie();
            tableauScores.push_back(score);
            ++k;
        }

        k = 0;
        cout << "Voici les resultats finaux :" << endl;
        while (k < nbJoueurs) {
            cout << tableauJoueurs[k] << " : " << tableauScores[k] << " points." << endl;
            ++k;
        }

        cout << endl << "Vous voulez rejouer ? (o/n) :" << endl;
        cin >> replay;
        cout << "Ca marche !" << endl << endl;
    }
    return 0;
}

int partie() {
    string mot, result;
    mot = selectMot();
    string motmelange = melange(mot);
    int essais = 0;
    int s(0);
    unsigned short int coefMultLose(0), coefMultWin(0);
    while (essais != 5) {
        cout << "\nQuel est ce mot ? : " << motmelange << endl;
        cin >> result;
        if (result != mot) {
            ++essais;
            ++coefMultLose;
            coefMultWin = 0;
            s -= 100 * coefMultLose;
            if (essais != 5) {
                cout << "Loupe, bois " << essais << " gorgee(s)." << endl
                    << "Tu perds " << 100 * coefMultLose << " points." << endl
                    << "Tu as donc " << s << " points." << endl
                    << "Il te reste " << 5 - essais << " essai(s)" << endl;
            }
            else {
                cout << "Ah t'as perdu mec... Bois 5 gorgees" << endl
                    << "Tu finis avec " << s << " points." << endl << endl;
                return s;
            }
        }
        else {
            ++coefMultWin;
            s += 100 * coefMultWin;
            cout << "\nlourd tu as trouve " << endl
                << "Tu gagnes " << 100 * coefMultWin << " points." << endl
                << "Tu as donc " << s << " points." << endl;
            coefMultLose = 0;
        }
    }
    return 0;
}

string melange(string m) {
    srand(time(0));

    int position;
    string pile;

    while (m.size() != 0) {
        position = rand() % m.size();
        pile += m[position];
        m.erase(position, 1);
    }
    return pile;
}

string selectMot(){
    ifstream dico("dico.txt");
    if (dico) {
        string Mot;
        dico.seekg(0, ios::end);
        int taille = dico.tellg();

        //choix aléatoire de l'offset qui va placer le "curseur c++" dans le fichier txt
        srand(time(0));
        int offset = rand();

        //Déplacement "curseur c++" jusqu'au début de ligne puis lecture de la ligne
        dico.seekg(offset, ios::beg);
        char curseur;
        if(offset > taille-2 && offset <= taille){
            offset = taille-2;
        }
        while (offset > 0 && curseur != '\n'){
            dico.seekg(offset, ios::beg);
            --offset;
            dico.get(curseur);
        }
        switch(offset){
            case 0:
                dico.seekg(offset, ios::beg);
                getline(dico, Mot);
                break;
            default:
                getline(dico, Mot);
                break;
        }
        return Mot;
    }
    else {
    cout << "ERREUR : Le fichier ne peut pas etre lu." << endl;
    exit(EXIT_FAILURE);
    }
}
