#ifndef BERSERKER_H
#define BERSERKER_H
#include "Personnage.h"
using namespace std;
//Classe Berserker dérivée de Personnage. 
class Berserker : public Personnage {
public:
    // Constructeur qui initialise un Berserker avec un nom
    Berserker(string nom);
    // Attaque puissante infligeant des dégâts importants
    void frappePunitive(Personnage &cible);
    // Attaque encore plus dévastatrice, au prix d'énergie
    void coupDechaine(Personnage &cible);
    // Surcharge de l'attaque spéciale du personnage
    void attaqueDelta(Personnage &cible);
};
#endif

