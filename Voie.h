/*************************************************************************
                           Voie  -  Description
                             -------------------
    début                : 19/03/2014
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : mohamed.haidara@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Voie> (fichier Voie.h) -------
#if ! defined ( VOIE_H )
#define VOIE_H

//------------------------------------------------------------------------
// Rôle de la tâche <Voie>
// Cette tache gere l'arrivée des voitures sur le Carrefour
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

// void Voie();
// Mode d'emploi : Gestion des voies
//
// Contrat :
//

// void Voie(int fileVoitures, int sem, int shmid, TypeVoie typeVoie);
// Mode d'emploi : Gere l'arrivée des voitures sur le carrefour
//
// Contrat : Fournir des indentifiants de semaphores, boite aux lettres et
// memoire partagées valides avec les bons droits.
void Voie(int fileVoitures, int sem, int shmid, TypeVoie typeVoie);


#endif // VOIE_H

