#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array> 
#include <vector> 
#include <cassert>
#include <span>
//#include <cppitertools/itertools.hpp>
#include <map>

using namespace std ;
// using namespace iter ;

void creerDictionnaire(string fpDico, char delimiteur, size_t tailleDico, string dictionnaireSortie[][2]) {
    ifstream dictionnaire(fpDico) ;

    if (!dictionnaire.is_open()) { // vérifie si le fichier est ouvert pour éviter de travailler dans le vide
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl ;
        exit(1) ;
    } 

    string liste ;
    for (int i = 0 ; i < tailleDico && getline(dictionnaire, liste) ; i++) {
        string mot = ""s, genreNombre = ""s, definition = ""s ;
        size_t posDelimiteur = uint(liste.find(delimiteur)) ; // trouve la première occurence du caractère 'delimiteur'
        if (posDelimiteur < liste.length()) {
            mot = liste.substr(0, posDelimiteur) ; // extrait le mot
        }

        size_t posDelimiteurNo2 = liste.find(delimiteur, posDelimiteur + 1) ; // trouve la seconde occurence de 'delimiteur'
        if (posDelimiteurNo2 < liste.length()) {
            genreNombre = liste.substr(posDelimiteur + 1, posDelimiteurNo2 - posDelimiteur - 1) ; // extrait le genre et la classe grammaticale
            definition = liste.substr(posDelimiteurNo2 + 1) ; // extrait la définition

            dictionnaireSortie[i][0] = mot + " (" + genreNombre + ")" ;
            dictionnaireSortie[i][1] = definition ;
        }
    }

    dictionnaire.close() ;
}

int main() {
    string fpDico = "/Users/elias/Desktop/INF1015/TP1/data/dictionnaire.txt" ;
    char del = '\t' ;
    size_t taille = 4 ;
    string dico[taille][2] ;
    creerDictionnaire(fpDico, del, taille, dico) ;

    size_t tailleMax = 0 ;
    int indiceMax = 0 ;
    for (int i = 0 ; i < taille ; i++) {
        string mot = dico[i][0].substr(0, dico[i][0].find(" ")) ;
        if (mot.length() > tailleMax) {
            tailleMax = mot.length() ;
            indiceMax = i ;
        }
    }

    cout << "Le plus long mot du dictionnaire est : \n " << dico[indiceMax][0] << " : " << dico[indiceMax][1] << endl ;
}