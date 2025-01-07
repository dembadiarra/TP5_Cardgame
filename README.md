#    Tp – Projet – Card Game

Objectif:
Vous devez réaliser la base d’un card game contenant à minima les personnages jouables et leur
mécanique de combat tel que précisez ci dessous :

Personnage de base :
Caractéristiques :
- Pt de vie : quantité de point de vie du personnage
- Attaque : défini la valeur de base sans modification d’une
attaque
- Défense : quantité de dégats réduits par le personnage.
- Vitesse : multiplicateur de temps entre chaque action du
personnage
- Energie : jauge d’accumulation d’énergie si cette valeur atteint
100 le personnage peut utiliser son abilité spéciale.
Abilités :
- Frappe préventive : Attaque de base infilgeant un montant de
degats égale à la quantité d’attaque du personnage, génère 10 point d’énèrgie.
- Blast : frappe améliorée: Attaque infligeant 1.5 x montant d’attaque, génère 15 point d’énèrgie.
- Action spéciale – Attaque Delta : Attaque infligeant 3.5 x montant d’attaque, consomme 100 point
d’énèrgie et ne peut ètre utilisé qu’a 100 point d’énèrgie.

code personnage.h
``` #ifndef PERSONNAGE_H
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
  ```
code personnage.cpp
```  #include "Personnage.h"
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
 ```
Personnage améliorer : Berserker
Le personnage Berserker est une évolution du personnage de base et
est donc un heritié de la classe précédente. Il possède toutes les
caractéristique et les abilités du personnage de base

Abilités évolué :
- Frappe punitive : Attaque infilgeant un montant de degats égale à
30% du montant de point de vie max du personnage et consomme
10% de ses points de vie, génère 20 point d’énèrgie.
- Coup déchainé : frappe améliorée: Attaque infligeant 50% du
montant de point de vie max du personnage et consomme 15% de
ses points de vie, génère 30 point d’énèrgie.
- Action spéciale – Movement Alpha : Attaque infligeant 75% du montant de point de vie max et
régenère 50% de ses points de vie, consomme 100 point d’énèrgie et ne peut ètre utilisé qu’a 100
point d’énèrgie.

code Berserker.h :
``` 
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
 ```
code Berserker.cpp : 
```  #include "Berserker.h"
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
 ```
Personnage améliorer : SnowQueen
Le personnage SnowQueen est une évolution du
personnage de base et est donc un heritié de la
classe précédente. Il possède toutes les
caractéristique et les abilités du personnage de
base

Abilités évolué :
- Javelot de glace : Attaque infilgeant un montant
de degats égale à 125% du montant d’attaque du personnage, génère 20 point d’énèrgie.
- Vent glaciale : frappe ameliorée: Attaque infligeant 150% du montant d’attaque du personnage,
génère 30 point d’énèrgie.
- Action spéciale – LetItGo : Attaque infligeant 175% du montant d’attaque du personnage,
consomme 100 point d’énèrgie et ne peut ètre utilisé qu’a 100 point d’énèrgie.

code SnowQueen.h : 
```  #ifndef SNOWQUEEN_H
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
 ```
code SnowQueen.cpp :
```  #include "SnowQueen.h"
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
 ```
Partie 1 :
Créer chaque classe avec son fichier header distinct ainsi que son fichier de définition.
Le constructeur de base de la classe personnage contient le nom et le nb de point de vie du
personnage
Créer le main du programme qui gérera les action du combat qui sera en tour par tour tel que défini
ci dessous:
- le personnage qui a le plus de vitesse joue en premier
- vous devez choisir l’action a éxecuter en rentrant 1 pour attaque de base, 2 pour l’attaque
améliorée et 3 pour l’action spéciale, attention l’action spéciale nécessite 100 point d’énèrgie.
- le personnage vainqueur est celui qui a un montant de point de vie supérieur à 0 quand les autres
sont à 0.
Tester chacune des abilités.

code main.cpp : 
``` #include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include "Berserker.h"
#include "SnowQueen.h"

using namespace std;

// Fonction pour afficher l'état actuel du combat
void afficherEtatCombat(Personnage &p1, Personnage &p2) {
    cout << "\nÉtat du Combat\n";
    cout << p1.getNom() << " - Point de vie : " << p1.getPointsDeVie() << " | " << p1.getEnergie() << " point d énérgie\n";
    cout << p2.getNom() << " - Point de vie : " << p2.getPointsDeVie() << " | " << p2.getEnergie() << "point d énérgie\n";
    cout << "____________________________________________________\n";
}

// Fonction pour gérer le tour de combat entre deux personnages
void tourDeCombat(Personnage &p1, Personnage &p2) {
 while (p1.estEnVie() && p2.estEnVie()) {
        // Le personnage le plus rapide attaque en premier
        if (p1.getVitesse() >= p2.getVitesse()) {
            p1.frappePreventive(p2);  // p1 attaque en premier
            cout << p1.getNom() << " inflige " << p2.getPointsDeVie() << " points de dégâts à " << p2.getNom() << " !\n";
        } else {
            p2.frappePreventive(p1);  // p2 attaque en premier
            cout << p2.getNom() << " inflige " << p1.getPointsDeVie() << " points de dégâts à " << p1.getNom() << " !\n";
        }
    
        // Affichage de l'état après le premier coup
        afficherEtatCombat(p1, p2);
        
       


        // Vérification de la survie du deuxième personnage
        if (!p2.estEnVie()) {
            cout << p2.getNom() << " est vaincu !\n";
            break;
        }

        // Tour de p1 : Choix de l'action
        cout << "Choisissez une action pour " << p1.getNom() << ": 1. Frappe, 2. Blast, 3. Attaque Spéciale\n";
        int choix;
        cin >> choix;

        // Traitement de l'action de p1
        switch (choix) {
            case 1: p1.frappePreventive(p2); break;
            case 2: p1.blast(p2); break;
            case 3: p1.attaqueDelta(p2); break;
            default: cout << "Choix invalide, vous perdez votre tour.\n"; break;
        }

        // Affichage de l'état après l'action de p1
        afficherEtatCombat(p1, p2);

        // Vérification de la survie de p2
        if (!p2.estEnVie()) {
            cout << p2.getNom() << " est vaincu !\n";
            break;
        }

        // Tour de p2 : Choix de l'action
        cout << "Choisissez une action pour " << p2.getNom() << ": 1. Frappe, 2. Blast, 3. Attaque Spéciale\n";
        cin >> choix;

        // Traitement de l'action de p2
        switch (choix) {
            case 1: p2.frappePreventive(p1); break;
            case 2: p2.blast(p1); break;
            case 3: p2.attaqueDelta(p1); break;
            default: cout << "Choix invalide, vous perdez votre tour.\n"; break;
        }

        // Affichage de l'état après l'action de p2
        afficherEtatCombat(p1, p2);

        // Vérification de la survie de p1
        if (!p1.estEnVie()) {
            cout << p1.getNom() << " est vaincu !\n";
            break;
        }
    }
}


int main() {
/*pour compiler :
g++ -o mon_programme mon_programme.cpp -lmysqlcppconn
*/

/*

GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;

________________________________________________________________________________________________________________


CREATE USER 'demba'@'localhost' IDENTIFIED BY '@Passciel2';
GRANT ALL PRIVILEGES ON cardgames* TO 'demba'@'localhost';
FLUSH PRIVILEGES;

*/
    cout << "Connexion avec la base de données établie !\n";
    cout << "___________________________________________\n";
    cout << "Utilisation de la table equipements :\n";
    cout << "Les personnages Berserker et Snowqueen utilisent leurs équipements\n";
    sql::mysql::MySQL_Driver *driver;
    /*on déclare le pointeur driver pour communiquer avec 
    le serveur mysql*/
    sql::Connection *con;
    /*on déclare le pointeur con qui représentera 
    la connexion avec la base de donnéés*/

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "demba", "@Passciel2");
    /*cette ligne fait la connexion avec le server mysql avec son adresse IP
    et son port 3306 ensuite on se connecte à l'utilisateur demba 
    et son mot de passe*/

    // Sélectionner la base de données
    con->setSchema("cardgames");
    /*Pour ce connecter à la base de données*/

    // Exemple de requête
    sql::PreparedStatement *pstmt;
    pstmt = con->prepareStatement("SELECT * FROM equipements");
    sql::ResultSet *res = pstmt->executeQuery();

    cout << "_________________________________________________________________________________________________________________________________\n";
    while (res->next()) 
    {
        std::cout 
        <<"  ID : " << res->getInt("id") <<"  | "
        <<", Nom : " << res->getString("nom") <<"   | "
        <<", bonusvie     : " << res->getString("bonusvie") <<"   | "
        <<", bonusattaque : " << res->getString("bonusattaque") <<"   | "
        <<", bonusdefense : " << res->getString("bonusdefense") <<"   | "
        <<", bonusvitesse : " << res->getString("bonusvitesse") <<"   | " <<endl;
    }
    cout << "_________________________________________________________________________________________________________________________________\n";
    cout << "Berserker gagne 60 points de vie\n" ;
    cout << "Berserker tape plus fort de 40 points\n" ;
    cout << "Berserker gagne 30 points de défense\n" ;
    cout << "Berserker gagne 35 points de vitesse\n" ;
    cout << "Snowqueen gagne 75 points de vie\n" ;
    cout << "Snowqueen tape plus fort de 90 points\n" ;
    cout << "Snowqueen gagne 33 points de défense\n" ;
    cout << "Snowqueen gagne 35 points de vitesse\n" ;
    cout <<"\n\n\n\n\n";

    delete res;
    delete pstmt;
    delete con;

    // Initialisation des personnages Berserker et Snow Queen
    Berserker berserker("Berserker");
    SnowQueen snowQueen("SnowQueen");

    // Démarrage du combat
    tourDeCombat(berserker, snowQueen);

    return 0;
}
 ```

Partie 2 :
Chaque personnage est équipé d’une arme et des pièces d’armure qui sont un heaume, un gilet, des
gants et des bottes.
Chacune de ses pièces possèdent 4 caractéristiques aléatoire qui peuvent ètre des bonus de vie,
d’attaque, de défense et de vitesse.
Un personnage ayant équipé ces équipement obtiendra un bonus correspondant au montant de
chaque caractéristique présente sur la pièce d’équipement et qui sera ajouté aux caractéristique de
base du personnage.

Créer une base de données contenant ces pièces par catégorie, heaume, gilet, gants, bottes et arme puis on joute ces modification a votre programme créer à la partie 1.

#   acceder à la base de donnée(BDD) ;
-Pour acceder à la base faut se connecter à mysql avec :
``` sudo mysql -u root -p ```

-ensuite on séléctionne la BDD avec :
``` USE cardgames ; ```

-on crée la table "équipements" :
``` CREATE TABLE Equipments (
    id INT AUTO_INCREMENT PRIMARY KEY,
    type ENUM('heaume', 'gilet', 'gants', 'bottes', 'arme') NOT NULL,
    nom VARCHAR(50) NOT NULL,
    bonusvie INT DEFAULT 0,
    bonusattaque INT DEFAULT 0,
    bonusdefense INT DEFAULT 0,
    bonusvitesse INT DEFAULT 0,
    personnage_id INT NOT NULL
);
```
Insertion des données : 
```  INSERT INTO Equipments (id, type, nom, bonusvie, bonusattaque, bonusdefense, bonusvitesse, personnage_id)
VALUES
(1, 'heaume', 'Heaume du Berserker', 20, 400, 10, 5, 1),
(2, 'gilet', 'Gilet du Berserker', 30, 400, 5, 0, 1),
(3, 'gants', 'Gants du Berserker', 10, 400, 5, 10, 1),
(4, 'bottes', 'Bottes du Berserker', 0, 400, 10, 20, 1),
(5, 'arme', 'Arme du Berserker', 0, 400, 0, 0, 1),
(6, 'heaume', 'Heaume de Snowqueen', 25, 400, 13, 5, 2),
(7, 'gilet', 'Gilet de Snowqueen', 40, 400, 5, 0, 2),
(8, 'gants', 'Gants de Snowqueen', 10, 400, 5, 10, 2),
(9, 'bottes', 'Bottes de Snowqueen', 0, 400, 10, 20, 2),
(10, 'arme', 'Arme de Snowqueen', 0, 400, 0, 0, 2);
```
Requête pour afficher les données sous ce format
Pour afficher la table dans un terminal SQL, utilisez :
``` SELECT * FROM Equipments;
```
 




















