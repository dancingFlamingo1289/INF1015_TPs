// Solutionnaire du TD3 INF1015 hiver 2025
// Par Francois-R.Boyer@PolyMtl.ca
#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <memory>
#include <functional>
#include <cassert>
#include <span>
#include <iomanip>
#include <sstream>

using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms() = default;
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	shared_ptr<Acteur> trouverActeur(const string& nomActeur);
	span<Film*> enSpan() const;
	int size() const { return nElements; }
	void detruire(bool possedeLesFilms = false);
	Film*& operator[] (int index) { assert(0 <= index && index < nElements);  return elements[index]; }
	Film* trouver(const function<bool(const Film&)>& critere) {
		for (auto& film : enSpan())
			if (critere(*film))
				return film;
		return nullptr;
	}

	friend Film* lireFilm(istream& fichier, ListeFilms& listeFilms);
private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
};

template <typename T>
class Liste {
public:
	Liste() = default;
	explicit Liste(int capaciteInitiale) :  // explicit n'est pas matière à ce TD, mais c'est un cas où c'est bon de l'utiliser, pour ne pas qu'il construise implicitement une Liste à partir d'un entier, par exemple "maListe = 4;".
		capacite_(capaciteInitiale),
		elements_(make_unique<shared_ptr<T>[]>(capacite_))
	{
	}
	Liste(const Liste<T>& autre) :
		capacite_(autre.nElements_),
		nElements_(autre.nElements_),
		elements_(make_unique<shared_ptr<T>[]>(nElements_))
	{
		for (int i = 0; i < nElements_; ++i)
			elements_[i] = autre.elements_[i];
	}
	//NOTE: On n'a pas d'operator= de copie, ce n'était pas nécessaire pour répondre à l'énoncé. On aurait facilement pu faire comme dans les notes de cours et définir l'operator= puis l'utiliser dans le constructeur de copie.
	//NOTE: Nos constructeur/operator= de move laissent la liste autre dans un état pas parfaitement valide; il est assez valide pour que la destruction et operator= de move fonctionnent, mais il ne faut pas tenter d'ajouter, de copier ou d'accéder aux éléments de cette liste qui "n'existe plus". Normalement le move sur les classes de la bibliothèque standard C++ laissent les objets dans un "valid but unspecified state" (https://en.cppreference.com/w/cpp/utility/move). Pour que l'état soit vraiment valide, on devrait remettre à zéro la capacité et nombre d'éléments de l'autre liste.
	Liste(Liste<T>&&) = default;  // Pas nécessaire, mais puisque c'est si simple avec unique_ptr...
	Liste<T>& operator= (Liste<T>&&) noexcept = default;  // Utilisé pour l'initialisation dans lireFilm.

	void ajouter(shared_ptr<T> element)
	{
		assert(nElements_ < capacite_);  // Comme dans le TD précédent, on ne demande pas la réallocation pour ListeActeurs...
		elements_[nElements_++] = move(element);
	}

	Liste& operator=(const Liste& autre) {
		if (this != &autre) {
			capacite_ = autre.capacite_;
			nElements_ = autre.nElements_;
			elements_ = make_unique<shared_ptr<T>[]>(autre.capacite_);
			for (int i = 0; i < autre.nElements_; i++) {
				if (autre.elements_[i]) {
					elements_[i] = autre.elements_[i];
				}
			}
		}
		return *this;
	}

	// Noter que ces accesseurs const permettent de modifier les éléments; on pourrait vouloir des versions const qui retournent des const shared_ptr, et des versions non const qui retournent des shared_ptr.  En C++23 on pourrait utiliser "deducing this".
	shared_ptr<T>& operator[] (int index) const { assert(0 <= index && index < nElements_); return elements_[index]; }
	span<shared_ptr<T>> enSpan() const { return span(elements_.get(), nElements_); }

private:
	int capacite_ = 0, nElements_ = 0;
	unique_ptr<shared_ptr<T>[]> elements_;
};

using ListeActeurs = Liste<Acteur>;

class Affichable {
public :
	virtual ~Affichable() = default ;

	friend ostream& operator<<(std::ostream& os, const Affichable& affichable) {
		affichable.afficher(os);
		return os;
	}
private :
	virtual void afficher(ostream& os) const = 0 ;
};

class Item : public Affichable {
public :
	Item() = default;
	Item(string titre, int anneeSortie) : titre_(titre), anneeSortie_(anneeSortie) {}
	virtual ~Item() = default;

	string getTitre() { return titre_; }
	int getAnneeSortie() { return anneeSortie_; }

	string getTitre() const { return titre_; }
	int getAnneeSortie() const { return anneeSortie_; }

	void setTitre(const string& titre) { titre_ = titre; }
	void setAnneeSortie(int anneeSortie) { anneeSortie_ = anneeSortie; }
private :
	string titre_;
	int anneeSortie_ = 0;

	virtual void afficher(ostream& os) const override = 0 ;
};

class Livre : public Item {
public : 
	Livre() = default;
	Livre(string titre, string auteur, int anneeSortie, int nMillionsCopies, int nPages)
		: Item(titre, anneeSortie), auteur_(auteur), nMillionsCopies_(nMillionsCopies), nPages_(nPages) {}
	
	Livre(const std::string& chaineLivre) : Livre() {
		istringstream stream(chaineLivre);
		string titre, auteur;
		int anneeSortie, nMillionsCopies, nPages;

		if (!(stream >> std::quoted(titre) >> anneeSortie >> std::quoted(auteur) >> nMillionsCopies >> nPages)) {
			throw std::runtime_error("Erreur de lecture de la ligne !");
		}

		setTitre(titre) ;
		setAnneeSortie(anneeSortie) ;
		auteur_ = auteur ;
		nMillionsCopies_ = nMillionsCopies ;
		nPages_ = nPages ;
	}

private :
	void afficher(std::ostream& os) const override {
		os << "Titre: " << getTitre() << endl;
		os << "  Auteur: " << auteur_ << "  Année : " << getAnneeSortie() << endl;
		os << "  Copies vendues: " << nMillionsCopies_ << " millions" << endl;
		os << "  Nombre de pages: " << nPages_ << endl;
	}

	string auteur_ ;
	int nMillionsCopies_ = 0, nPages_ = 0;
};

struct Acteur {
	string nom;
	int anneeNaissance = 0;
	char sexe = '\0';

	void afficher(std::ostream& os) {
		os << "  " << nom << ", " << anneeNaissance << " " << sexe << endl;
	}
};

class Film : public Item {
public :
	Film() = default ;
	Film(string titre, string realisateur, int anneeSortie, int recette, ListeActeurs& acteurs)
		: Item(titre, anneeSortie), realisateur_(realisateur), recette_(recette), acteurs_(acteurs) {}

	friend shared_ptr<Acteur> ListeFilms::trouverActeur(const std::string& nom);

	friend Film* lireFilm(istream& fichier, ListeFilms& listeFilms);

private :
	void afficher(ostream& os) const override {
		os << "Titre: " << getTitre() << endl;
		os << "  Réalisateur: " << realisateur_ << "  Année :" << getAnneeSortie() << endl;
		os << "  Recette: " << recette_ << "M$" << endl;

		os << "acteurs_:" << endl;
		for (const shared_ptr<Acteur>& acteur : acteurs_.enSpan())
			(*acteur).afficher(os);
	}

	string realisateur_; // nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int recette_=0; // recette globale du film en millions de dollars
	ListeActeurs acteurs_;
};
