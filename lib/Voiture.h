/*************************************************************************
                           Voiture.h  -  description
                             -------------------
    début                : 23 Jan 2015
    copyright            : (C) 2015 par Mathieu Maranzana
    e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Voiture> (fichier Voiture.h) -----------
#if ! defined VOITURE_H
#define VOITURE_H

//------------------------------------------------------------------------
// rôle du module <Voiture>
//    ce module contient les paramètres liés aux voitures
//        * les constantes communes
//        * les types communs utilisés
//    ce module n'a pas de fichier réalisation associé
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////// INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"

//------------------------------------------------------------- Constantes
// les numéros identifiant les voitures entrant dans le carrefour sont
// sont définis dans l'intervalle [ min , max ] :

// génération manuelle de voiture (option 'M' au clavier)
const unsigned int numeroMinManuel =   1;
const unsigned int numeroMaxManuel = 199;

// génération automatique (dans le cas de la génération automatique de
// voitures à partir de la tâche <Générateur>)
const unsigned int numeroMinGenerateur = numeroMaxManuel + 1;
const unsigned int numeroMaxGenerateur = 999;

// attention :
//    * les deux intervalles doivent être disjoints
//    * comme la tâche <Générateur> est fournie, le second intervalle
//      ne peut pas être modifié

//------------------------------------------------------------------ Types
// structure définissant les caractéristiques d'une voiture
struct Voiture {
    TypeVoie     entree;  // voie d'entrée dans le carrefour
    TypeVoie     sortie;  // voie de sortie du carrefour
    unsigned int numero;  // numéro de la voiture
};

// structure d'un message déposé et retiré de la file de messages
// l'identifiant du message (champ <type>) désigne la voie d'entrée dans
// le carrefour (redondance avec le champ <entree> du message)
struct MsgVoiture {
    long type;            // identifiant du message (obligatoire)
    Voiture uneVoiture;   // structure voiture
};

#define TAILLE_MSG_VOITURE    sizeof ( Voiture )

#endif // VOITURE_H

