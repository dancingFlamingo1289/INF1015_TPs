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

const float GRAVITE_TERRE = 9.81 ;

float hauteurMaxBalle(float hauteurInitiale, float coeffRebond, int nbRebonds) {
    float h_i = hauteurInitiale ;
    
    for (int i = 0 ; i < nbRebonds ; i++) {
        float v_i, v_ip1, h_ip1 ;
        v_i = sqrt(2 * GRAVITE_TERRE * h_i) ;
        v_ip1 = coeffRebond * v_i ;
        h_ip1 = (v_ip1*v_ip1) / (2 * GRAVITE_TERRE) ;
        h_i = h_ip1 ;
    }

    return h_i ;
}

int main() {
    float hauteurInitiale, coeffRebond ;
    int nbRebonds ;

    cout << "Entrez la hauteur initiale de la balle en mètres, le nombre de rebonds souhaité et le coefficient de rebond espacés d'un espace." << endl ;
    cin >> hauteurInitiale >> nbRebonds >> coeffRebond ;

    if (hauteurInitiale < 0 || nbRebonds < 0) {
        cout << "La hauteur initiale de la balle et le nombre de rebonds souhaité doivent être positifs." << endl ;
        return 1 ;
    } else if (coeffRebond < 0 || coeffRebond > 1) {
        cout << "Le coefficient de rebond doit être compris entre 0 et 1." << endl ;
        return 1 ;
    } else {
        cout << "La hauteur de la balle après " << nbRebonds << " rebonds est de " << hauteurMaxBalle(hauteurInitiale, coeffRebond, nbRebonds) << " mètres." << endl ;
    }
}