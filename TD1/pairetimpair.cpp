#include <iostream> 
#include <iomanip>
#include <vector>
#include <cmath>
#include <sstream>
#include <random>


vector<int> liste_impair_pair(vector <int> a) {

	vector<int> impair;
	vector<int> pair;

	for (int i : a) {
		if (i % 2 == 0) {
			pair.push_back(i);
		}
		else {
			impair.push_back(i);
		}
	}
	for (int i : impair) {
		pair.push_back(i);
	}
	return pair;
}

/*
int main() {
	cout << "Pour créer le tableau de tallie 10, il faut entrer 10 nombres: " << endl;
	vector<int> tableau;
	int valeur;

	for (int i = 1; i <= 10; i++) {
		cout << "Tapez la valeur numero " << i << " : ";
		cin >> valeur;
		tableau.push_back(valeur);
	}

	vector<int> organiser = liste_impair_pair(tableau);

	cout << "Le tableau organisé: {";
	for (int i = 0; i < organiser.size(); i++) {
		cout << organiser[i];
		if (i < organiser.size() - 1) {
			cout << ", ";
		}
	}
	cout << "}" << endl;

}
*/