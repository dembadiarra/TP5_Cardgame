#include "Berserker.h"
#include <iostream>
using namespace std;

// Constructeur : initialise un Berserker avec des valeurs spécifiques (plus de points de vie, moins de défense)
Berserker::Berserker(string nom)
    : Personnage(nom, 180, 105, 40, 40) {}  // 120 PV, 20 attaque, 10 défense, 5 vitesse

// Frappe punitive : inflige des dégâts basés sur les PV actuels, mais le Berserker subit aussi des dégâts
void Berserker::frappePunitive(Personnage &cible) {
    int degats = pointsDeVie * 0.3;        // Inflige 30% des PV actuels en dégâts
    recevoirDegats(pointsDeVie * 0.1);     // Berserker subit 10% de ses PV en contrepartie
    cible.recevoirDegats(degats);          // La cible reçoit les dégâts
    energie += 20;                         // Augmente l'énergie du Berserker
    cout << nom << " utilise Frappe punitive !\n";
}

// Coup déchaîné : une attaque plus puissante qui inflige des dégâts plus importants mais coûte plus de PV
void Berserker::coupDechaine(Personnage &cible) {
    int degats = pointsDeVie * 0.5;        // Inflige 50% des PV actuels en dégâts
    recevoirDegats(pointsDeVie * 0.15);    // Berserker subit 15% de ses PV en contrepartie
    cible.recevoirDegats(degats);          // La cible reçoit les dégâts
    energie += 30;                         // Augmente l'énergie du Berserker
    cout << nom << " a utilise Coup déchaîné !\n";
}

// Attaque spéciale du Berserker, Mouvement Alpha, qui nécessite 100 d'énergie
void Berserker::attaqueDelta(Personnage &cible) {
    if (energie >= 100) {                              // Vérifie si le Berserker a assez d'énergie
        cible.recevoirDegats(pointsDeVie * 0.75);      // Inflige 75% des PV actuels en dégâts
        pointsDeVie += pointsDeVie * 0.5;              // Le Berserker regagne 50% de ses PV
        energie = 0;                                   // Réinitialise l'énergie après l'attaque
        cout << nom << " Mouvement Alpha utiliser !\n";
    } else {
        cout << nom << " n'a pas assez d'énergie pourvutiliser le Mouvement Alpha !\n";
    }
}

