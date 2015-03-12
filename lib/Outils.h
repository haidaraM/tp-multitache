/*************************************************************************
                           Outils.h  -  description
                             -------------------
    début                : 23 Jan 2015
    copyright            : (C) 2015 par Mathieu Maranzana
    e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Outils> (fichier Outils.h) -------------
#if ! defined OUTILS_H
#define OUTILS_H

//------------------------------------------------------------------------
// rôle du module <Outils>
//    ce module prend en charge la partie graphique de l'application
//    multitâche en gérant complètement le clavier et l'écran
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////// INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <cstdlib>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
// définition des types de terminaux supportés pour l'exécution de
// l'application multitâche
//    1. XTERM : terminal X par défaut
//    2. VT220 : terminal pour les connexions réseau (via ssh)
//               (VT220 englobe le cas vt100)
enum TypeTerminal { XTERM, VT220 };

// définition des modes vidéos mis en oeuvre lors des différents affichages
enum ModeVideo { NORMALE, INVERSE };

// définition du rendu des caractères lors des différents affichages
enum TypeCaractere { STANDARD, GRAS };

// définition des types d'opérations possibles sur le nombre de voitures
// invisibles en attente à chaque voie d'entrée du carrefour
enum TypeOperation { PLUS, MOINS };

// définition du nom de chaque voie d'entrée dans le carrefour
enum TypeVoie { AUCUNE, NORD, EST, SUD, OUEST };

// définition des zones particulières de l'écran (affichage et effacement)
enum TypeZone {
  ETAT_GENERATEUR,// état de la tâche <Générateur> (3 car.)
  NUMERO,         // numéro de la dernière voiture (3 car.)
  ENTREE,         // voie d'entrée (N,E,S ou O) de la dernière voiture (1 car.)
  SORTIE,         // voie de sortie (N,E,S ou O) de la dernière voiture (1 car.)
  COULEUR_AXE_NS, // couleur du feu pour l'axe N-S (6 car.)
  COULEUR_AXE_EO, // couleur du feu pour l'axe voie E-O (6 car.)
  TEMPS_AXE_NS,   // décompte temporel du feu pour l'axe N-S (3 car.)
  TEMPS_AXE_EO,   // décompte temporel du feu pour l'axe E-O (3 car.)
  DUREE_AXE_NS,   // durée du feu pour l'axe N-S (2 car.)
  DUREE_AXE_EO,   // durée du feu pour l'axe E-O (2 car.)
  HEURE,          // zone d'affichage de l'heure (8 car.)
  MESSAGE,        // zone d'affichage des messages d'erreurs (78 car.)
  MENU            // zone d'affichage des menus de l'application (78 car.)
};

/////////////////////////////////////////////////////////////////// PUBLIC
//---------------------------------------------------- Fonctions publiques
void Afficher ( TypeZone zone, unsigned int valeur,
                TypeCaractere caractere = STANDARD, ModeVideo mode = NORMALE );
// mode d'emploi :
//    <zone>     : définit la zone de l'écran concernée par l'opération
//                 d'affichage (MESSAGE, MENU, HEURE, ENTREE...)
//    <valeur>   : valeur entière non signée à afficher dans la <zone>
//    <caractere>: rendu des caractères lors de l'affichage de la <valeur>
//                 (par défaut, le rendu est <STANDARD>)
//    <mode>     : mode vidéo d'affichage de la <valeur> (par défaut, le
//                 mode d'affichage est <NORMALE)
//    - affiche l'entier non signé (<valeur>) selon le mode (<mode>) et le
//      rendu de caractères (<caractere>) choisis dans la bonne zone de
//      l'écran (<zone>)
//
// contrat :
//    - l'affichage de la valeur entière non signée ne doit pas dépasser la
//      taille de la zone utilisée pour cet affichage
//    - le comportement est indéterminé en cas de non-respect de la contrainte
//

void Afficher ( TypeZone zone, TypeVoie voie,
                TypeCaractere caractere = STANDARD, ModeVideo mode = NORMALE );
// mode d'emploi :
//    <zone>     : définit la zone de l'écran concernée par l'opération
//                 d'affichage (MESSAGE, MENU, HEURE, ENTREE...)
//    <voie>     : voie du carrefour (NORD, EST, SUD ou OUEST) à afficher
//                 dans la <zone>
//    <caractere>: rendu des caractères lors de l'affichage de la <voie>
//                 (par défaut, le rendu est <STANDARD>)
//    <mode>     : mode vidéo d'affichage de la <voie> (par défaut, le
//                 mode d'affichage est <NORMALE)
//    - affiche la voie (<voie>) selon le mode (<mode>) et le
//      rendu de caractères (<caractere>) choisis dans la bonne zone de
//      l'écran (<zone>)
//    - l'affichage se limite au premier caractère de la voie :
//          * NORD  => 'N'          * SUD   => 'S'
//          * EST   => 'E'          * OUEST => 'O'
//

void Afficher ( TypeZone zone, const char message [ ],
                TypeCaractere caractere = STANDARD, ModeVideo mode = NORMALE );
// mode d'emploi :
//    <zone>     : définit la zone de l'écran concernée par l'opération
//                 d'affichage (MESSAGE, MENU, HEURE, ENTREE...)
//    <message>  : contient le message sous forme d'une chaîne de caractères
//                 en convention C/C++ ('\0' en fin de chaîne)
//    <caractere>: rendu des caractères lors de l'affichage de la chaîne
//                 de caractères (par défaut, le rendu est <STANDARD>)
//    <mode>     : mode vidéo d'affichage de la chaîne de caractères (par
//                 défaut, le mode d'affichage est <NORMALE)
//    - affiche la chaîne de caractères (<message>) selon le mode (<mode>)
//      et le rendu de caractères (<caractere>) choisis dans la bonne zone
//      de l'écran (<zone>)
//
// contrat :
//    - le message doit être une chaîne de caractères au sens du C/C++ et
//      ne pas dépasser la taille de la zone utilisée pour l'affichage
//    - le comportement est indéterminé en cas de non-respect de ces
//      contraintes
//

pid_t DeplacerVoiture ( unsigned int numero,
                        TypeVoie entree, TypeVoie sortie );
// mode d'emploi :
//    <numero> : numéro de la voiture à déplacer
//    <entree> : identification de la voie d'entrée (point d'entrée)
//               (voie N, E, S ou O)
//    <sortie> : identification de la voie de sortie (point de sortie)
//               (voie N, E, S ou O)
//    - lance une nouvelle tâche (tâche fille) gérant le déplacement d'une
//      voiture sur le carrefour entre son point d'entrée (<entree>) et son
//      point de sortie (<sortie>)
//      => l'appelant n'est pas bloqué pendant cette opération et peut
//      continuer normalement ses activités (par exemple : lancement d'un
//      autre déplacement de voiture sur le carrefour)
//    - la synchronisation de fin avec la tâche fille peut se faire via
//      le signal <SIGCHLD> automatiquement déclenché vers la tâche mère
//      (l'appelant) à la mort de la tâche fille
//    - la tâche fille de déplacement d'une voiture sur le carrefour
//      est susceptible de réagir au signal de fin <SIGUSR2> en cas de fin
//      de l'application (utilisation de la commande adéquate)
//    - à la réception du signal <SIGUSR2>, la tâche fille de déplacement
//      d'une voiture sur le carrefour déclenche sa fin propre
//    - renvoie le PID de la tâche fille de déplacement d'une voiture
//      si elle est correctement lancée
//    - renvoie -1 en cas de problème
//
// contrat : aucun
//

void DessinerVoitureFeu ( unsigned int numero,
                          TypeVoie entree, TypeVoie sortie );
// mode d'emploi :
//    <numero> : numéro de la voiture qui arrive au feu
//    <entree> : identification de la voie d'entrée (point d'entrée)
//               (voie N, E, S ou O)
//    <sortie> : identification de la voie de sortie (point de sortie)
//               (voie N, E, S ou O)
//    - cette procédure dessine une voiture de numéro <numero> au niveau
//      du feu de la voie d'entrée définie par <entree>, si l'emplacement
//      est disponible
//    - si la place est déjà occupée par une autre voiture (voiture en
//      train de rentrer sur le carrefour), une nouvelle tentative de
//      dessin est effectuée périodiquement => le retour de cette procédure
//      n'est pas toujours immédiat
//    - le dessin de la voiture tient compte de la voie de sortie (défini
//      par le paramètre <sortie>). Par exemple, pour une voiture quittant
//      le carrefour par la voie E, le dessin de la voiture comporte le
//      caractère 'E'
//
// contrat : aucun
//

void Effacer ( TypeZone zone );
// mode d'emploi :
//    <zone> : zone de l'écran à effacer (MESSAGE, MENU...)
//    - efface la zone correspondante à l'écran
//
// contrat : aucun
//

void InitialiserApplication ( TypeTerminal terminal );
// mode d'emploi :
//    <terminal> : indique le type de terminal utilisé pour l'exécution
//                 de l'application multitâche
//      * XTERM : terminal de type XTERM (terminal X par défaut)
//      * VT220 : terminal de type VT220 (connexion réseau via ssh)
//    - modifie la gestion de la ligne de transmission et prépare l'écran
//      pour les besoins associés à la gestion graphique de l'application
//      multitâche :
//         1. suppression de l'écho;
//         2. retour immédiat après lecture d'un caractère (lecture au vol)
//         3. curseur en mode invisible
//         4. effacement de l'écran (curseur en (0,0) en haut et a gauche)
//    - initialise les paramètres indispensables au bon fonctionnement du
//      TP (par exemple : le générateur aléatoire)
//    - initialise les attributs graphiques de l'écran
//    - met en place les ressources systèmes nécessaires é la gestion graphique
//        * un sémaphore général avec 3 sémaphores élémentaires :
//           . sem 0 : mutex de gestion des conflits d'accès à l'écran
//           . sem 1 : mutex de gestion des conflits d'accès à la zone de
//                     mémoire partagée utilisée pour gérer le nombre
//                     de voitures en attente à chaque voie
//           . sem 2 : mutex de gestion des conflits d'accès à la zone de
//                     mémoire partagée utilisée pour définir les positions
//                     des voitures sur le carrefour (occupation du carrefour)
//        * une zone de mémoire partagée utilisée pour la mémorisation des
//          positions des voitures sur le carrefour et pour gérer le nombre de
//          voitures en attente à chaque voie
//
// ATTENTION: en cas d'"arrêt inopiné" de l'application multitâche (sortie de
//            l'application sans passer par <TerminerApplication>), les
//            ressources systèmes (sémaphore et mémoire partagée) ne seront
//            pas rendues au système et dans ce cas, la destruction manuelle
//            des ressources et tâches encore actives devient OBLIGATOIRE
//
//    - affiche le carrefour et son environnement
//
// contrat : aucun
//

void OperationVoie ( TypeOperation op, TypeVoie voieEntree );
// mode d'emploi :
//    <op>        : type d'opération à effectuer (<PLUS> ou <MOINS>)
//    <voieEntree>: voie concernée par l'opération (voie N, E, S ou N)
//    - gère le nombre de voitures en attente à la voie <voieEntree>
//      et non visible sur l'écran de la simulation
//    - la nouvelle valeur est affichée à l'écran (mise à jour de la zone)
//
// contrat : aucun
//

void TerminerApplication ( bool efface = true );
// mode d'emploi :
//    <efface> : demande d'effacement (ou de conservation) de l'écran en
//               fin d'exécution
//    - si <efface> = <true>, alors l'écran est effacé en fin d'exécution
//      sinon, le dessin est conservé (très utile en phase de mise au point)
//    - restaure l'état initial de la ligne de transmission et de l'écran
//         1. traitement normal des lectures au clavier ("bufférisées")
//         2. curseur en mode visible
//         3. effacement de l'écran (curseur en ( 0,0 ) en haut et à gauche),
//            si cela est demandé
//    - restitue les ressources systèmes (sémaphore, mémoire partagée)
//      utilisées pour la gestion de l'écran (gestion du trafic sur le
//      carrefour)
//
// contrat : aucun
//

#endif // OUTILS_H

