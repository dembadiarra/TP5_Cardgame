#include <mysql_driver.h>
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

