/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 17/03/2015
    copyright            : (C) Emilien Bai
    e-mail               : emilien.bai@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Mere> (fichier Mere.h) -------
#if ! defined ( MERE_H )
#define MERE_H

//------------------------------------------------------------------------
// Rôle de la tâche <MERE>
//Crée les sous taches de l'appilication ainsi que les zones de 
// partagées
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
int main (void);
//la tache pricipale de l'application
//

void masquage(int noSig);
//fonction vide masquant la reception des signaux

void terminer(pid_t pidHeure, pid_t pidGenerateur,pid_t voie,int fileVoitures, int semFeux);
//Fonction de terminaison de l'application




#endif // XXX_H

