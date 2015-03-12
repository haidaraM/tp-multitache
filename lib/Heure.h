/*************************************************************************
                           Heure.h  -  description
                             -------------------
    début                : 23 Jan 2015
    copyright            : (C) 2015 par Mathieu Maranzana
    e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Heure> (fichier Heure.h) -------------
#if ! defined HEURE_H
#define HEURE_H

//------------------------------------------------------------------------
// rôle de la tâche <Heure>
//    cette tâche est chargée de l'affichage périodique de l'heure
//    (toutes les <PERIODE> secondes (on pose <PERIODE> = 1 seconde))
//    dans la zone adéquate de l'écran du TP (en haut, à droite)
//    la fin de la tâche <Heure> est déclenchée à la réception du
//    signal de fin <SIGUSR2>
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////// INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <unistd.h>

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

/////////////////////////////////////////////////////////////////// PUBLIC
//---------------------------------------------------- Fonctions publiques
pid_t CreerEtActiverHeure ( void );
// mode d'emploi :
//    - cette fonction lance une tâche fille <Heure> chargée de
//      de l'affichage périodique (toutes les <PERIODE> secondes de l'heure
//      courante dans la zone <HEURE> de l'écran du TP
//    - la fin de la tâche <Heure> est déclenchée à la réception du
//      signal de fin <SIGUSR2>
//    - renvoie le PID de la tâche <Heure>, si sa création se passe bien
//    - renvoie -1 en cas d'échec à la création de la tâche <Heure>
//
// contrat : aucun
//


#endif // HEURE_H

