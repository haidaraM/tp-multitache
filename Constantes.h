/*************************************************************************
                           Constantes  -  description
                             -------------------
    début                : Constantes
    copyright            : (C) Constantes par Constantes
    e-mail               : Constantes
*************************************************************************/

//---------- Interface du module <Constantes> (fichier Constantes.h) ---------
#if ! defined ( CONSTANTES_H )
#define CONSTANTES_H

//------------------------------------------------------------------------
// Rôle du module <Constantes>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
const char REFERENCE[]="./TP-Multitache/Carrefour";

// Indice memoire partagée
const int INDICE_ETAT_FEU_NS = 0;
const int INDICE_ETAT_FEU_EO = 1;
const int INDICE_TEMPS_NS = 2;
const int INDICE_TEMPS_EO = 3;

// Temps par défaut des feux
const int TEMPS_FEU_NS = 20;
const int TEMPS_FEU_EO = 10;

// Informations pour les voies
const unsigned int NB_VOIES = 4;
const unsigned int INDICE_VOIE_NORD = 0;
const unsigned int INDICE_VOIE_SUD = 1;
const unsigned int INDICE_VOIE_OUEST = 2;
const unsigned int INDICE_VOIE_EST = 3;
//------------------------------------------------------------------ Types


#endif // CONSTANTES_H

