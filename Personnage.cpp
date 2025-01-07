#include "Personnage.h"
#include <iostream>
using namespace std;
// Constructeur : initialise les attributs de base du personnage
Personnage::Personnage(string nom, int pv, int attaque, int defense, int vitesse)
    : nom(nom), pointsDeVie(pv), attaque(attaque), defense(defense), vitesse(vitesse), energie(0) {}
// Retourne les points de vie actuels
int Personnage::getPointsDeVie() const { return pointsDeVie; }
// Retourne la vitesse du personnage
int Personnage::getVitesse() const { return vitesse; }
// Retourne l'énergie actuelle
int Personnage::getEnergie() const { return energie; }
// Retourne le nom du personnage
string Personnage::getNom() const { return nom; }
// Gère la réception de dégâts en tenant compte de la défense
void Personnage::recevoirDegats(int degats) {
    int reduction = degats - defense;
    pointsDeVie -= (reduction > 0) ? reduction : 0;  // Si la réduction est négative, ne pas infliger de dégâts
}
// Vérifie si le personnage est encore en vie
bool Personnage::estEnVie() const { return pointsDeVie > 0; }
// Frappe rapide, ajoute de l'énergie au personnage après l'attaque
void Personnage::frappePreventive(Personnage &cible) {
    cible.recevoirDegats(attaque);     // Inflige des dégâts à la cible
    energie += 10;                     // Augmente l'énergie du personnage
    cout << nom << " utilise Frappe préventive !\n";
}
// Attaque puissante qui consomme plus d'énergie
void Personnage::blast(Personnage &cible) {
    cible.recevoirDegats(attaque * 1.5);  // Inflige plus de dégâts
    energie += 15;                        // Ajoute plus d'énergie
    cout << nom << " utilise Blast !\n";
}
// Attaque spéciale qui nécessite un certain niveau d'énergie
void Personnage::attaqueDelta(Personnage &cible) {
    if (energie >= 100) {                 // Vérifie si le personnage a assez d'énergie
        cible.recevoirDegats(attaque * 3.5);  // Inflige des dégâts massifs
        energie = 0;                          // Réinitialise l'énergie après l'attaque
        cout << nom << " utilise Attaque Delta !\n";
    } else {
        cout << nom << " n'a pas assez d'énergie pour l'Attaque Delta !\n";
    }
}

