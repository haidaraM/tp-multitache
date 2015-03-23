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
#include <stdlib.h>
#include <signal.h>
#include <sys/msg.h>

//------------------------------------------------------ Include personnel
#include "GestionMenu.h"
#include "Outils.h"
#include "Menu.h"
#include "Voiture.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static bool etat_generateur = false;
static unsigned int numero_voiture = 1;
static pid_t pid_generateur;
static int file_voitures;

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
void GestionMenu(pid_t generateur, int fileVoitures)
// Algorithme :
//
{
    file_voitures = fileVoitures;
    pid_generateur = generateur;
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
            kill(pid_generateur, SIGSTOP);
            Afficher(ETAT_GENERATEUR,"OFF",GRAS);
        }
        else
        {
            kill(pid_generateur, SIGCONT);
            Afficher(ETAT_GENERATEUR,"ON",GRAS);
        }
        etat_generateur = !etat_generateur;
    }
}

void Commande ( TypeVoie entree, TypeVoie sortie )
{

    Voiture voiture = {entree, sortie, numero_voiture++};
    MsgVoiture msgVoiture = {entree,voiture};

    int resultat = msgsnd(file_voitures,&msgVoiture,TAILLE_MSG_VOITURE-sizeof(long),IPC_NOWAIT);
    Effacer(MESSAGE);
    if(resultat == -1)
    {
        Afficher(MESSAGE,"Probleme de dépot dans la boite aux lettres");
    }
    else
        Afficher(MESSAGE,"Depot ok");
}

void Commande ( TypeVoie voie, unsigned int duree )
{
    //TODO : Gestion de la commande D => accès memoire partagée
}
