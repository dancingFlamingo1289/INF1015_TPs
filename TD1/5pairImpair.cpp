#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array> 
#include <vector> 
#include <cassert>
#include <span>
//#include <cppitertools/itertools.hpp>

using namespace std ;
// using namespace iter ;

void orgTableauPairImpair(int tableau[], int taille, int tableauOrganise[]) {
    int nbPairs = 0 ;
    for (int i = 0 ; i < taille ; i++) {
        if (tableau[i] % 2 == 0) {
            nbPairs++ ;
        }
    }
    
    int tableauPair[nbPairs], tableauImpair[taille - nbPairs] ;
    int dernierIndPair = 0, dernierIndImpair = 0 ;
    for (int i = 0 ; i < taille ; i++) {
        int nb = tableau[i] ;
        
        if (nb % 2 == 0) {
            tableauPair[dernierIndPair] = nb ;
            dernierIndPair++ ;
        } else {
            tableauImpair[dernierIndImpair] = nb ;
            dernierIndImpair++ ;
        }
    }

    for (int i = 0 ; i < nbPairs ; i++) {
        tableauOrganise[i] = tableauPair[i] ;
    }

    for (int i = 0 ; i < taille - nbPairs ; i++) {
        tableauOrganise[nbPairs + i] = tableauImpair[i] ;
    }
}

int main() {
    int taille = 10 ;
    int tableau[taille], tableauOrganise[taille] ;
    
    for (int i = 0 ; i < taille ; i++) {
        cout << "tableau[" << i+1 << "] = " ;
        cin >> tableau[i] ;
    }

    orgTableauPairImpair(tableau, taille, tableauOrganise) ;

    cout << "Tableau organisé : " ;
    for (int i = 0 ; i < taille ; i++) {
        cout << tableauOrganise[i] << " " ;
    }
    cout << endl ;
}