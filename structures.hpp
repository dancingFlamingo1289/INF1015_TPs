#pragma once
// Structures mémoires pour une collection de films.
#include <string>
#include <cassert>
#include <span>
#include <memory>
#include <sstream>
#include <cppitertools/range.hpp>

using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms() = default;
	ListeFilms(const std::string& nomFichier);
	ListeFilms(const ListeFilms& l) { assert(l.elements == nullptr); } // Pas demandé dans l'énoncé, mais on veut s'assurer qu'on ne fait jamais de copie de liste, car la copie par défaut ne fait pas ce qu'on veut.  Donc on ne permet pas de copier une liste non vide (la copie de liste vide est utilisée dans la création d'un acteur).
	~ListeFilms();
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	shared_ptr<Acteur> trouverActeur(const std::string& nomActeur) const;
	std::span<Film*> enSpan() const;
	int size() const { return nElements; }

	Film* operator[](int index) {
		return elements[index];
	}
	
	Film* chercherFilm(function<bool(Film*)> critere);
private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
	bool possedeLesFilms_ = false; // Les films seront détruits avec la liste si elle les possède.
};

struct Acteur
{
public:
	std::string nom = ""; int anneeNaissance = 0; char sexe = '0';
	//ListeFilms joueDans = {};

	Acteur(const Acteur& autre) = default;
	Acteur() = default;

	friend ostream& operator<<(ostream& os, const Acteur acteur) {
		os << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
		return os ;
	}
};

template <typename T>
class Liste {
public:

	span<shared_ptr<T>> spanListe() { return span<shared_ptr<T>>(elements_.get(), nElements_); }
	span<shared_ptr<T>> spanListe() const { return span<shared_ptr<T>>(elements_.get(), nElements_); }
		
	unique_ptr<shared_ptr<T>[]> setElements() {
		return elements_;
	}
	/*unique_ptr<shared_ptr<T>[]> getElements() const {
		return elements_;
	}*/


	int getCapacite() const{
		return capacite_;
	}

	int getCapacite(){
		return capacite_;
	}

	int getNElements() const{
		return nElements_;
	}
	int getNElements() {
		return nElements_;
	}

	void setElements(unique_ptr<shared_ptr<T>[]> nouvElements) {
		elements_ = move(nouvElements);
	}
	
	void setCapacite(int nouvCapacite) {
		capacite_ = nouvCapacite;
	}

	void setNElements(int nouvNElement) {
		nElements_ = nouvNElement;
	}
	
	Liste(int nouvCapacite, int nElems) : capacite_(nouvCapacite), nElements_(nElems) {
		elements_ = make_unique<shared_ptr<T>[]>(capacite_);
	}
	
		Liste() = default;
		Liste(int capaciteinitial): nElements_(capaciteinitial), elements_(make_unique<shared_ptr<T>[]>(capaciteinitial)) {};
		
		//Liste(Liste&& autre) noexcept
		//	: elements_(move(autre.elements_)), nElements_(autre.nElements_) {
		//	autre.nElements_ = 0; // Pour éviter que l'autre instance ait des données invalides

		//}

		Liste& operator=(Liste&& autre) noexcept {
			elements_ = move(autre.elements_);
			nElements_ = autre.nElements_;
			autre.elements_ = nullptr;
			return *this;
		}
		shared_ptr<T> operator[](int index) {
			return elements_[index];
		}


		Liste(const Liste& laCopie) {
			capacite_ = laCopie.capacite_;
			nElements_ = laCopie.nElements_;
			elements_ = make_unique<shared_ptr<T>[]>(capacite_);
			for (int i = 0; i < nElements_; ++i) {
				elements_[i] = laCopie.elements_[i];
			}
		}
		Liste& operator=(const Liste& autre) {
			if (this != &autre) {
				capacite_ = autre.capacite_;
				nElements_ = autre.nElements_;
				elements_ = make_unique<shared_ptr<T>[]>(capacite_);
				for (int i = 0; i < nElements_; i++) {
					if (autre.elements_[i]) {
						elements_[i] = autre.elements_[i];
					}
				}
			}
			return *this;
		}
	
		/*Liste& operator=(const Liste& autre) {
			if (this != &autre) {
				capacite = autre.capacite;
				nElements = autre.nElements;
				elements = make_unique<shared_ptr<T>[]>(autre.capacite);
				for (int i = 0; i < autre.nElements; i++) {
					if (autre.elements[i]) {
						elements[i] = autre.elements[i];
					}
				}
			}
			return *this;
		}*/
	
	
		/*span<shared_ptr<T>> spanListe() { return span<shared_ptr<T>>(elements_.get(), nElements_); }
		span<shared_ptr<T>> spanListe() const { return span<shared_ptr<T>>(elements_.get(), nElements_); }*/
private:
	int capacite_ = 0;
	int nElements_ = 0;
	unique_ptr<shared_ptr<T>[]> elements_; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.

};
using ListeActeurs = Liste<Acteur>;


struct Film
{
	std::string titre = "", realisateur = ""; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 0, recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;

	Film() : titre(""), realisateur(""), anneeSortie(0), recette(0) {}



	Film(Film&& autre) noexcept
		: titre(move(autre.titre)), realisateur(move(autre.realisateur)),
		anneeSortie(autre.anneeSortie), recette(autre.recette),
		acteurs(move(autre.acteurs)) {}

	Film(const Film& autre)
		: titre(autre.titre),
		realisateur(autre.realisateur),
		anneeSortie(autre.anneeSortie),
		recette(autre.recette),
		acteurs() {
		
		acteurs.setCapacite(autre.acteurs.getCapacite());
		acteurs.setNElements(autre.acteurs.getNElements());

		acteurs.setElements(make_unique<shared_ptr<Acteur>[]>(acteurs.getCapacite()));
		acteurs = autre.acteurs ;
	}

	//Film(const Film& autre) = default;

	Film& operator=(const Film& autre) {
		if (this != &autre) {
			titre = autre.titre;
			realisateur = autre.realisateur;
			anneeSortie = autre.anneeSortie;
			recette = autre.recette;
			acteurs = autre.acteurs;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Film f) {
		os << "Titre: " << f.titre << "\n"
			<< "Réalisateur: " << f.realisateur << "\n"
			<< "Année: " << f.anneeSortie << "\n"
			<< "Recette: " << f.recette << "M$\n";

		os << "Acteurs:\n" << endl;
		for (shared_ptr<Acteur> acteur : f.acteurs.spanListe())
			os << *acteur ;
		
		return os;
	}
};
