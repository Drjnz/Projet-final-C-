#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Produit
{
private:
    std::string nom;
    double prixBase;
    double prixAjuste;
    int quantite;

public:
    Produit(std::string nom, double prixBase, double prixAjuste, int quantite) :
        nom(nom),
        prixBase(prixBase),
        prixAjuste(prixAjuste),
        quantite(quantite)
    {
        std::cout << nom << " a ete creee" << std::endl;

    }
    virtual ~Produit()
    {
        std::cout << "\n" << nom << " est detruit" << "\n" << std::endl;

    }

    std::string getNom() const
    {
        return nom;
    }
    double getPrixBase() const
    {
        return prixBase;
    }
    double getPrixAjuste() const
    {
        return prixAjuste;
    }
    int getQuantite() const
    {
        return quantite;
    }
    void setPrixAjuste(double prix) { prixAjuste = prix; }
    void ajouterQuantite(int quantite) { quantite += quantite; }
    void retirerQuantite(int quantite) { quantite -= quantite; }
};

class Entreprise
{
private:
    int id;
    std::string type;
    double capital;
    int employes;
    int niveau;

public:
    Entreprise(int id, std::string type, double capital, int employe, int niveau) :
        id(id),
        type(type),
        capital(capital),
        employes(employe),
        niveau(niveau)
    {
        std::cout << "L'entreprise " << id << " a ete creee" << std::endl;

    }
    virtual ~Entreprise()
    {
        std::cout << "L'entreprise" << id << " est detruite" << "\n" << std::endl;

    }
    void produire(Produit& produit)
    {
        int production = niveau * 20;
        produit.ajouterQuantite(production);
        std::cout << "Entreprise " << id << " a produit " << production << " kgs de " << produit.getNom() << "\n" << std::endl;
    }

    void acheter(Produit& produit, int quantite)
    {
        double cout = produit.getPrixAjuste() * quantite;
        if (capital >= cout)
        {
            capital -= cout;
            produit.retirerQuantite(quantite);
            std::cout << "Entreprise " << id << " a achete " << quantite << " kgs de " << produit.getNom() << std::endl;
        }
        else
        {
            std::cout << "Fonds insuffisants pour l'entreprise " << id << std::endl;
        }
    }

    void investir(double montant)
    {
        if (capital >= montant)
        {
            capital -= montant;
            niveau++;
            std::cout << "Entreprise " << id << " Niveau atteint: " << niveau << "\n" << std::endl;
        }
        else
        {
            std::cout << " Capital insuffisant pour investir." << std::endl;
        }
    }

    void afficherStatistiques() const
    {
        std::cout << "Entreprise " << id << " | Type: " << type
            << " | Capital: " << capital << " | Employes: " << employes
            << " | Niveau: " << niveau << std::endl;
    }
};

class Marche
{
public:
    std::vector<std::shared_ptr<Entreprise>> entreprises;
    std::vector<Produit> produits;

    void ajusterPrix()
    {
        for (auto& produit : produits)
        {
            produit.setPrixAjuste(produit.getPrixBase() * (1.0 + 0.1 * (100 - produit.getQuantite()) / 100));
        }
    }

    void afficherStatistiquesGlobales() const
    {
        std::cout << "Statistiques du marche :" << "\n" << std::endl;
        for (const auto& entreprise : entreprises)
        {
            entreprise->afficherStatistiques();
        }
        for (const auto& produit : produits)
        {
            std::cout << "Produit: " << produit.getNom() << " | Prix ajuste: " << produit.getPrixAjuste()
                << " | Quantite: " << produit.getQuantite() << std::endl;
        }
    }
};

int main()
{
    Marche marche;


    auto entreprise1 = std::make_shared<Entreprise>(1, "Primaire", 10000, 5, 1);
    auto entreprise2 = std::make_shared<Entreprise>(2, "Secondaire", 15000, 8, 2);
    auto entreprise3 = std::make_shared<Entreprise>(3, "Primaire", 12000, 9, 1);
    auto entreprise4 = std::make_shared<Entreprise>(4, "secondaire", 16000, 4, 2);
    auto entreprise5 = std::make_shared<Entreprise>(5, "secondaire", 13000, 5, 1);



    marche.entreprises.push_back(entreprise1);
    marche.entreprises.push_back(entreprise2);
    marche.entreprises.push_back(entreprise3);
    marche.entreprises.push_back(entreprise4);
    marche.entreprises.push_back(entreprise5);

    Produit coton("Coton", 50, 45, 100);
    Produit vetements("Vetement", 200, 150, 50);
    Produit ble("ble", 2000, 150, 50);
    Produit farine("farine", 1200, 150, 50);
    Produit cerelac("cerelac", 2500, 1000, 50);

    marche.produits.push_back(coton);
    marche.produits.push_back(vetements);
    marche.produits.push_back(ble);
    marche.produits.push_back(farine);
    marche.produits.push_back(cerelac);

    for (int tour = 0; tour < 5; ++tour)
    {
        std::cout << "\n" << "  Statistique du jour  " << std::endl;
        std::cout << "\n" << "Jour " << tour + 1 << std::endl;
        entreprise1->produire(coton);
        entreprise2->acheter(coton, 20);
        entreprise2->produire(vetements);
        entreprise1->investir(1000);
        entreprise3->produire(ble);
        entreprise4->acheter(ble, 10);
        entreprise4->produire(farine);
        entreprise5->acheter(ble, 10);
        entreprise5->produire(cerelac);

        marche.ajusterPrix();
        marche.afficherStatistiquesGlobales();
    }

    return 0;
}