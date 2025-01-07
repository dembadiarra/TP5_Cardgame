#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>
using namespace std;
//Classe de base représentant un personnage avec des attributs
class Personnage {
protected:
    string nom;          // Nom du personnage
    int pointsDeVie;     // Points de vie actuels
    int attaque;         // Puissance d'attaque
    int defense;         // Valeur de défense
    int vitesse;         // Vitesse du personnage
    int energie;         // Énergie en rapport avec les capaciter
public:
    // Constructeur pour initialiser le personnage
    Personnage(string nom, int pv, int attaque, int defense, int vitesse);
    // Accesseurs(en gros les getters) pour les points de vie, la vitesse, l'énergie et le nom
    int getPointsDeVie() const;
    int getVitesse() const;
    int getEnergie() const; 
    string getNom() const;

    // Capacités d'attaque
    void frappePreventive(Personnage &cible); // Attaque rapide
    void blast(Personnage &cible);            // Attaque puissante 
    virtual void attaqueDelta(Personnage &cible); // Attaque spéciale 

    // Méthodes pour recevoir des dégâts et vérifier si le personnage est encore en vie
    void recevoirDegats(int degats);
    bool estEnVie() const;
};

#endif

