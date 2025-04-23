#pragma once
// Structures mémoires pour une collection de films.

#include <string>

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
	public :
		ListeFilms() {
			capacite_ = 10 ;
			nElements_ = 0 ;
			elements_ = nullptr ;
		}

		int& capacite() {
			return capacite_ ;
		}

		const int& capacite() const {
			return capacite_ ;
		}

		int& nElements() {
			return nElements_ ;
		}

		const int& nElements() const {
			return nElements_;
		}

		Film**& elements() {
			return elements_ ;
		}

		const Film* const* elements() const { // Fonction const renvoyant un pointeur constant
			return elements_;
		}
	private :
		int capacite_, nElements_ ;
		Film** elements_ = {}; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
};

struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
};

struct Film
{
	std::string titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};

struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};
