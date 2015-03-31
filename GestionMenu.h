/*************************************************************************
                           GestionMenu  -  description
                             -------------------
    début                : 19/03/2015
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : mohamed.haidara@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <GestionMenu> (fichier GestionMenu.h) -------
#if ! defined ( GestionMenu_H )
#define GestionMenu_H

//------------------------------------------------------------------------
// Rôle de la tâche <GestionMenu>
// Cette tache gère le menu et le clavier
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// void GestionMenu ( pid_t generateur, int fileVoitures, int shmid, int semaphore );
// Mode d'emploi :
//
// Contrat : Fournir des indentifiants de semaphores, boite aux lettres et
// memoire partagées valides avec les bons droits et le pid du génerateur
void GestionMenu(pid_t generateur, int fileVoitures, int shmid, int semaphore);

#endif // GestionMenu_H

