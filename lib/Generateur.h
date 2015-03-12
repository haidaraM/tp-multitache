/*************************************************************************
                           Generateur.h  -  description
                             -------------------
    début                : 23 Jan 2015
    copyright            : (C) 2015 par Mathieu Maranzana
    e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Générateur> (fichier Generateur.h) ---
#if ! defined GENERATEUR_H
#define GENERATEUR_H

//------------------------------------------------------------------------
// rôle de la tâche <Générateur>
//    cette tâche permet de simuler l'arrivée de voitures sur le
//    carrefour avec un laps de temps aléatoire entre deux véhicules
//    les voies d'entrée et de sortie sur le carrefour sont choisies
//    aléatoirement pour chaque véhicule
//    le numéro de voiture est incrémenté au fur et à mesure et appartient
//    à l'intervalle [ <numéroMinGenerateur> , <numéroMaxGenerateur> ]
//    (numéro en boucle)
//    cette tâche peut fonctionner avec un déséquilibre dans la génération
//    aléatoire de voitures sur le carrefour (déséquilibre du trafic entre
//    les axes)
//    cette tâche met aussi à jour l'interface graphique de l'application
//    (rubriques <Voiture> et <En attente> de la zone <Etat>)
//    la fin de la tâche <Générateur> est déclenchée à la réception du
//    signal de fin <SIGUSR2>
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////// INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <unistd.h>

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

/////////////////////////////////////////////////////////////////// PUBLIC
//---------------------------------------------------- Fonctions publiques
pid_t CreerEtActiverGenerateur ( int desequilibre, int msgId );
// mode d'emploi :
//    <desequilibre>: déséquilibre du tirage aléatoire des voies d'entrée
//    <msgId>       : identifiant de la file de messages où sont déposées
//                    les voitures qui pénètrent sur le carrefour
//    - si <desequilibre> vaut -1, toutes les voitures arrivent sur les
//      voies N ou S
//    - si <desequilibre> vaut 0, aucune voie n'est favorisée
//    - si <desequilibre> > 0, il faut l'arrivée d'au moins <desequilibre>
//      voitures sur les voies N ou S avant d'avoir une voiture sur les
//      voies E ou O
//    - si <desequilibre> < -1, on retient la valeur absolue
//    - génère aléatoirement l'arrivée de voitures par l'une des quatre
//      voies sur le carrefour
//    - les messages déposés dans la boîte aux lettres <msgId> sont de
//      type C/C++ <MsgVoiture> : la description de ce type est fournie
//      dans le fichier <Voiture.h>
//
//    - cette fonction lance une tâche fille <Générateur> chargée de
//      de l'arrivée aléatoire de voitures sur le carrefour
//    - cette tâche met à jour les différents affichages de la zone <Etat>
//      de l'écran du TP (rubriques <Voiture> et <En attente>)
//    - le laps de temps entre deux arrivées de voitures est aléatoire
//      (intervalle fixé)
//    - les numéros de voitures simulés sont dans l'intervalle
//      [ <numeroMinGenerateur> , <numeroMaxGenerateur> ] (incrémentation
//      de 1 en 1 et en boucle)
//    - la tâche <Générateur> est par défaut suspendue au lancement
//      (la génération automatique de voitures est désactivée)
//    - la fin de la tâche <Générateur> est déclenchée à la réception du
//      signal de fin <SIGUSR2>
//    - renvoie le PID de la tâche <Générateur>, si sa création se passe bien
//    - renvoie -1 en cas d'échec à la création de la tâche <Génération>
//
// contrat :
//    <numeroMinGenerateur> doit être inférieure à 1000
//    <numeroMaxGenerateur> doit être inférieure à 1000
//    - les deux constantes <numeroMinGenerateur> et <numeroMaxGenerateur>
//      doivent définir un intervalle cohérent et compatible avec l'intervalle
//      des numéros réservés pour une génération manuelle d'une arrivée de
//      voitures sur le carrefour (intervalles disjoints)
//    - le comportement est indéterminé en cas de non-respect de cette
//      contrainte
//

#endif // GENERATEUR_H

