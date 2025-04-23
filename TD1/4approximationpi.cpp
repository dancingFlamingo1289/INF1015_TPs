#include <iostream> 
#include <iomanip>
#include <vector>
#include <cmath>
#include <sstream>
#include <random>

using namespace std;


double generatice_points(int nb_iteration) {


	double nb_point_total = nb_iteration;
	double nb_point_cercle = 0;

	for (int i = 0; i < nb_iteration; i++) {

		double x = (double(rand()) / RAND_MAX) * 2.0 - 1.0;
		double y = (double(rand()) / RAND_MAX) * 2.0 - 1.0;

		if (pow(x, 2) + pow(y, 2) < 1) {
			nb_point_cercle++;
		}
	}

	double pi_appro = 4 * nb_point_cercle / nb_point_total;

	return pi_appro;
}

double calcul_ecart(double approximation) {

	double pi = 3.141593;                               

	return (abs(approximation - pi) / pi * 100);
}

int main() {

	srand(unsigned(time(nullptr)))

	cout << "Entrez le nombre d'iteration: ";
	double iteration;
	cin >> iteration;

	if (iteration < 0) {
		cout << "valeur invalide, entrez une autre valeur: ";
		cin >> iteration;
	}


	double approximation = generatice_points(iteration);
	cout << "la valeur approximative est: " << fixed << setprecision(6) << approximation << endl;

	cout << "l'ecart relatif entre la valeur reel et approximative est: " << calcul_ecart(approximation) << '%' << endl;
}
