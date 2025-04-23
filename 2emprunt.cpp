#include <iostream>
#include <cmath>

using namespace std;


void recolteur_donnees(double& variable, double intervalle_inf, double intervalle_sup) {


	while (variable > intervalle_sup or variable < intervalle_inf) {

		cout << "La valeur est invalide. Entrez une nouvelle valeur :";
		cin >> variable;
	}
}

void nombre_de_mois(double argent_prete, double montant_mensuel, double taux_annuel) {
	double taux_mensuel = taux_annuel / 100 / 12;
	int nb_mois = 0;
	double argent_a_payer = argent_prete;
	double reste_dernier_mois = 0;
	 

	while (argent_a_payer > 0) {

		argent_a_payer = argent_a_payer * (1 + taux_mensuel) - montant_mensuel;
		nb_mois++;

		if (argent_a_payer < 0) {
			argent_a_payer = 0;
		}

		if (argent_a_payer < montant_mensuel) {
			reste_dernier_mois += argent_a_payer;
		}
	}
	cout << "vous avez besoin de " << nb_mois << " mois pour embourcer votre dette." << endl;

	// on ne sait pas si le montant pay� au dernier mois est �gale au montant pay� au autres mois, alors on ne le considere pas dans le nombre de mois et on le rajoute tout seul.

	double interet_preteur = montant_mensuel * (nb_mois - 1) + reste_dernier_mois - argent_prete;
	cout << "la somme des interets per�us par le preteur est: " << interet_preteur << "$";

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

	nombre_de_mois(argent_prete, montant_mensuel, taux_annuel);
	return 0;
}
