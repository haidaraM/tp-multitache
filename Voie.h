/*************************************************************************
                           Voie  -  description
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
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"
//------------------------------------------------------------- Constantes
const unsigned int NB_VOIES = 4;
const unsigned int INDICE_VOIE_NORD = 0;
const unsigned int INDICE_VOIE_SUD = 1;
const unsigned int INDICE_VOIE_OUEST = 2;
const unsigned int INDICE_VOIE_EST = 3;
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

void Voie(int fileVoitures, TypeVoie typeVoie);


#endif // VOIE_H

