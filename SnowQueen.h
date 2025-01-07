#ifndef SNOWQUEEN_H
#define SNOWQUEEN_H
#include "Personnage.h"
using namespace std;

// Déclaration de la classe SnowQueen, héritée de Personnage
class SnowQueen : public Personnage {
public:
    // Constructeur : initialise une SnowQueen avec un nom spécifique
    SnowQueen(string nom);

    // Méthodes spécifiques à SnowQueen pour ses attaques
    void javelotDeGlace(Personnage &cible);  // Attaque avec un javelot de glace
    void ventGlacial(Personnage &cible);     // Attaque avec un souffle glacial
    void attaqueDelta(Personnage &cible);    // Attaque spéciale "Delta" de la Reine des Neiges
};

#endif

