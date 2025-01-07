#include "SnowQueen.h"
#include <iostream>
using namespace std;

// Constructeur : initialise une SnowQueen avec ses attributs spécifiques
// 100 PV, 15 en attaque, 8 en défense, et 7 en vitesse
SnowQueen::SnowQueen(string nom)
    : Personnage(nom, 180, 105, 41, 42) {} 

// Javelot de glace : attaque infligeant 125% de l'attaque de base
// Augmente l'énergie de la SnowQueen de 20 après l'attaque
void SnowQueen::javelotDeGlace(Personnage &cible) {
    cible.recevoirDegats(attaque * 1.25);  // Inflige 125% des dégâts d'attaque
    energie += 20;                         // Ajoute 20 points d'énergie
    cout << nom << " utilise Javelot de glace !\n";
}

// Vent glacial : attaque plus puissante, inflige 150% des dégâts d'attaque
// Augmente l'énergie de 30 après l'attaque
void SnowQueen::ventGlacial(Personnage &cible) {
    cible.recevoirDegats(attaque * 1.5);   // Inflige 150% des dégâts d'attaque
    energie += 30;                         // Ajoute 30 points d'énergie
    cout << nom << " utilise Vent glacial !\n";
}

// Attaque spéciale "LetItGo" : nécessite 100 d'énergie pour être déclenchée
// Inflige 175% des dégâts d'attaque, et réinitialise l'énergie après l'attaque
void SnowQueen::attaqueDelta(Personnage &cible) {
    if (energie >= 100) {                  // Vérifie si l'énergie est suffisante
        cible.recevoirDegats(attaque * 1.75);  // Inflige 175% des dégâts d'attaque
        energie = 0;                          // Réinitialise l'énergie à 0
        cout << nom << " utilise LetItGo !\n"; // Annonce l'utilisation de l'attaque spéciale
    } else {
        cout << nom << " n'a pas assez d'énergie pour LetItGo !\n";  // Message si l'énergie est insuffisante
    }
}

