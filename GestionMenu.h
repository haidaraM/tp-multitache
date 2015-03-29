/*************************************************************************
                           GestionMenu  -  description
                             -------------------
    début                : GestionMenu
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : GestionMenu
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
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
void GestionMenu(pid_t generateur, int fileVoitures, int shmid);

#endif // GestionMenu_H

