/*************************************************************************
                           Constantes  -  description
                             -------------------
    début                : 25/03/2015
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : mohamed.haidara@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Constantes> (fichier Constantes.h) ---------
#if ! defined ( CONSTANTES_H )
#define CONSTANTES_H

//------------------------------------------------------------------------
// Rôle du module <Constantes>
// Cette interface quelques constantes qui sont utilisées par differents modules
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
//------------------------------------------------------------- Constantes
const char REFERENCE[]="./TP-Multitache/Carrefour";

// Indice memoire partagée
const int INDICE_ETAT_FEU_NS = 0;
const int INDICE_ETAT_FEU_EO = 1;
const int INDICE_TEMPS_NS = 2;
const int INDICE_TEMPS_EO = 3;

// Temps par défaut des feux
const int DUREE_INIT_NS = 20;
const int DUREE_INIT_EO = 10;
const int ROUGE = 0;
const int ORANGE = 1;
const int VERT = 2;

// Informations pour les voies
const unsigned int NB_VOIES = 4;


// Repertoires

const int NB_SONS=4;
const std::string REPERTOIRE_SON("./lib_audio/sounds/");

const int MEMOIRE_GENERATEUR = 4;
const int INDICE_SOUND_GENERATEUR = 0;
const std::string SOUND_GENERATEUR("generateur.wav");

const int MEMOIRE_CAR_STAR = 5;
const int INDICE_SOUND_CART_START = 1;
const std::string SOUND_CAR_START("car-star.aiff");

const int MEMOIRE_DUREE = 6;
const int INDICE_SOUND_DUREE = 2;
const std::string SOUND_DUREE("duree.wav");

const int MEMOIRE_TIMER = 7;
const int INDICE_SOUND_TIMER = 3;
const std::string SOUND_TIMER("timer_3.flac");


//------------------------------------------------------------------ Types


#endif // CONSTANTES_H

