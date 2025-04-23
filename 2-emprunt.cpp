#include <iostream>
#include <cmath>

using namespace std;


void recolteur_donnees(double& variable, double intervalle_inf, double intervalle_sup) {


	while (variable > intervalle_sup or variable < intervalle_inf) {

		cout << "La valeur est invalide. Entrez une nouvelle valeur :";
		cin >> variable;
	}
}

int nombre_de_mois(double argent_prete, double montant_mensuel, double taux_annuel) {

	double taux_mensuel = taux_annuel / 100 / 12;
	int nb_mois = 0;
	double argent_a_payer = argent_prete;
	double reste_dernier_mois = 0;


	while (argent_a_payer > 0) {

		argent_a_payer = argent_a_payer * (1 + taux_mensuel) - montant_mensuel;
		nb_mois++;
	}
	return nb_mois;
}

double interet_preteur1(double argent_prete, double montant_mensuel, double taux_annuel, int nb_mois) {

	double argent_a_payer = argent_prete;
	double reste_dernier_mois = 0;
	double taux_mensuel = taux_annuel / 100 / 12;
	int i;

	for (i = 0; i < nb_mois; i++) {

		argent_a_payer = argent_a_payer * (1 + taux_mensuel) - montant_mensuel;

		if (argent_a_payer < 0) {
			argent_a_payer = 0;
		}

		if (argent_a_payer < montant_mensuel) {
			reste_dernier_mois += argent_a_payer;
		}
	}
	double interet_preteur = montant_mensuel * (nb_mois - 1) + reste_dernier_mois - argent_prete;
	return interet_preteur;
}

int main() {

	double montant_mensuel;
	double argent_prete;
	double taux_annuel;


	cout << "entrez la somme d'argent pretee: ";
	cin >> argent_prete;
	recolteur_donnees(argent_prete, 0, numeric_limits<double>::infinity());

	cout << "entrez le montant rembource chaque mois: ";
	cin >> montant_mensuel;
	recolteur_donnees(montant_mensuel, 0, numeric_limits<double>::infinity());

	cout << "entrez le taux d'interet annuel: ";
	cin >> taux_annuel;
	recolteur_donnees(taux_annuel, 0, 100);

	int nb_mois = nombre_de_mois(argent_prete, montant_mensuel, taux_annuel);
	cout << "vous avez besoin de " << nb_mois << " mois pour embourcer votre dette." << endl;

	double interet_preteur = interet_preteur1(argent_prete, montant_mensuel, taux_annuel, nb_mois);
	cout << "la somme des interets perçus par le preteur est: " << interet_preteur << "$";
	return 0;
}
// finiii
