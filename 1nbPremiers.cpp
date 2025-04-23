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

bool estPremier(int n, int& premierDiviseur) {
    const int FACTEUR_MAX = sqrt(n) ;
    int facteur = 3 ;

    if (n % 2 == 0) {
        premierDiviseur = 2 ;
        return false ;
    }

    for (int facteur = 3 ; facteur <= FACTEUR_MAX ; facteur++) {
        if (n % facteur == 0) {
            premierDiviseur = facteur ;
            return false ;
        }
    }
    
    premierDiviseur = -1 ;
    return true ;
}

int main() {
    int monNombre = 0, premierDiviseur ;
    cout << "Entrez un nombre entier : " ;
    cin >> monNombre ;

    if (estPremier(monNombre, premierDiviseur)) {
        cout << "Ce nombre est premier." ;
    } else {
        cout << "Ce nombre n'est pas premier. Son premier diviseur est " << premierDiviseur << "." ;
    }
    
    return 0 ;
}