/*************************************************************************
                           GestionMenu  -  description
                             -------------------
    début                : GestionMenu
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : GestionMenu
*************************************************************************/

//---------- Réalisation de la tâche <GestionMenu> (fichier GestionMenu.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <stdlib.h>
#include "GestionMenu.h"
#include "Outils.h"
#include "Menu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static bool etat_generateur = false;
static pid_t pid_generateur;

//TODO : recuperer indentifiant boite aux lettres voitures
//TODO : recuperer le pid du generateur
//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GestionMenu()
// Algorithme :
//
{
	Menu();
} //----- fin de Nom

void Commande ( char code )
{
	if(code == 'Q')
	{
		exit(0);
	}
    else if(code == 'G')
    {
        Effacer(ETAT_GENERATEUR);
        if(etat_generateur)
        {
            Afficher(ETAT_GENERATEUR,"OFF",GRAS);
        }
        else
        {
            Afficher(ETAT_GENERATEUR,"ON",GRAS);
        }
        etat_generateur = !etat_generateur;
    }
}

void Commande ( TypeVoie entree, TypeVoie sortie )
{
    //TODO : Gestion de la commande M
}

void Commande ( TypeVoie voie, unsigned int duree )
{
    //TODO : Gestion de la commande D
}
