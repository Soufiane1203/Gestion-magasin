#include <iostream>
#include <string>

using namespace std;

// Classe de base Produit
class Produit {
protected:
    string nom;
    double prix;

public:
    // Constructeur avec liste d'initialisation
    Produit(string n, double p) : nom(n), prix(p) {}

    // Méthode d'affichage virtuelle
    virtual void afficher() {
        cout << "Nom: " << nom << ", Prix: " << prix << " euros" << endl;
    }

    // Getter pour le nom du produit
    string getNom() const {
        return nom;
    }

    // Getter pour le prix du produit
    double getPrix() const {
        return prix;
    }

    // Destructeur virtuel
    virtual ~Produit() {}
};

// Classe dérivée Alimentaire
class Alimentaire : public Produit {
protected:
    string dateExpiration;

public:
    // Constructeur avec liste d'initialisation
    Alimentaire(string n, double p, string d) : Produit(n, p), dateExpiration(d) {}

    // Méthode d'affichage redéfinie
    void afficher() override {
        Produit::afficher();
        cout << "Date d'expiration: " << dateExpiration << endl;
    }
};

// Classe dérivée Electronique
class Electronique : public Produit {
protected:
    int garantie;

public:
    // Constructeur avec liste d'initialisation
    Electronique(string n, double p, int g) : Produit(n, p), garantie(g) {}

    // Méthode d'affichage redéfinie
    void afficher() override {
        Produit::afficher();
        cout << "Garantie: " << garantie << " mois" << endl;
    }
};

// Classe Magasin
class Magasin {
private:
    int capaciteMax; // Capacité maximale du magasin
    Produit** produits; // Tableau de pointeurs vers des objets Produit
    int taille; // Nombre actuel de produits dans le magasin

public:
    // Constructeur avec capacité maximale
    Magasin(int capacite) : capaciteMax(capacite), produits(new Produit*[capacite]), taille(0) {}

    // Méthode pour ajouter un produit
    void ajouterProduit(Produit* produit) {
        if (taille < capaciteMax) {
            produits[taille++] = produit;
        } else {
            cout << "Capacite max atteinte" << endl;
        }
    }

    // Méthode pour afficher tous les produits
    void afficherProduits() {
        for (int i = 0; i < taille; i++) {
            produits[i]->afficher();
        }
    }

    // Méthode pour rechercher un produit par son nom et retourner un pointeur vers le produit
    Produit* rechercherParNom(string nom) {
        for (int i = 0; i < taille; i++) {
            if (produits[i]->getNom() == nom) {
                return produits[i];
            }
        }
        return nullptr;
    }

    // Méthode pour rechercher un produit par son prix et retourner un pointeur vers le produit
    Produit* rechercherParPrix(double prix) {
        for (int i = 0; i < taille; i++) {
            if (produits[i]->getPrix() == prix) {
                return produits[i];
            }
        }
        return nullptr;
    }

    // Destructeur
    ~Magasin() {
        delete[] produits; // Libération de la mémoire allouée pour le tableau de produits
    }
};

// Fonction principale
int main() {
    // Création du magasin avec une capacité maximale de 2 produits
    Magasin monMagasin(2);

    // Demander à l'utilisateur d'ajouter des produits
    cout << "=== Ajout de produits au magasin ===" << endl;

    for (int i = 0; i < 2; ++i) {
        string typeProduit;
        string nomProduit;
        double prixProduit;

        cout << "Quel type de produit ajouter (Alimentaire / Electronique) ? ";
        cin >> typeProduit;
        cin.ignore(); // Pour consommer le retour chariot laissé par cin

        cout << "Nom du produit ? ";
        getline(cin, nomProduit);

        cout << "Son prix ? ";
        cin >> prixProduit;

        if (typeProduit == "Alimentaire") {
            string dateExpiration;
            cout << "Date d'expiration ? ";
            cin >> dateExpiration;
            monMagasin.ajouterProduit(new Alimentaire(nomProduit, prixProduit, dateExpiration));
        } else if (typeProduit == "Electronique") {
            int garantie;
            cout << "Garantie (en mois) ? ";
            cin >> garantie;
            monMagasin.ajouterProduit(new Electronique(nomProduit, prixProduit, garantie));
        } else {
            cout << "Type de produit non valide !" << endl;
        }
    }

    // Affichage de tous les produits dans le magasin
    cout << "=== Détails de tous les produits dans le magasin ===" << endl;
    monMagasin.afficherProduits();

    // Recherche d'un produit par nom
    string nomRecherche;
    cout << "Entrez le nom du produit à rechercher : ";
    cin >> nomRecherche;
    cout << "Résultat de la recherche par nom : " << endl;
    Produit* produitNom = monMagasin.rechercherParNom(nomRecherche);
    if (produitNom) {
        produitNom->afficher();
    } else {
        cout << "Produit non trouvé." << endl;
    }

    // Recherche d'un produit par prix
    double prixRecherche;
    cout << "Entrez le prix du produit à rechercher : ";
    cin >> prixRecherche;
    cout << "Résultat de la recherche par prix : " << endl;
    Produit* produitPrix = monMagasin.rechercherParPrix(prixRecherche);
    if (produitPrix) {
        produitPrix->afficher();
    } else {
        cout << "Produit non trouvé." << endl;
    }

    return 0;
}
