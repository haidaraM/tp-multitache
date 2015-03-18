/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 17/03/15
    copyright            : (C) Emilien Bai
    e-mail               : emilien.bai@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Mere> (fichier Mere.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "Heure.h"


#include "GestionMenu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

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
//type Nom ( liste de paramètres )
// Algorithme :
//
//----- fin de Nom
int main (void)
{	//handler de masquage
	struct sigaction action;
	action.sa_handler = masquage;
	sigaction (SIGINT, &action, NULL); // masquage du Ctl+C
	sigaction (SIGCHLD, &action, NULL);// masquage du signal de mort d'un fils 
	sigaction (SIGUSR2, &action, NULL);// masquage de SIGUSR2
	
	//les pid des taches filles
	pid_t pidHeure, pidMenu;
	
	InitialiserApplication(XTERM);
	//Création de la tache Heure
	pidHeure = CreerEtActiverHeure();
	
	//Simulation de la pĥase moteur		
	//sleep(10);
	if((pidMenu=fork())==0)
	{
		// TODO : me donner le pid du generateur
		GestionMenu(0);
	}
	else
	{
		waitpid(pidMenu, 0, 0);
		//envoi de sigusr2 à heure : commande de kill
		kill( pidHeure , SIGUSR2);
		//waitpid
		waitpid(pidHeure, 0, 0);
		TerminerApplication();
		return 0;
	}
	
}

void masquage(int noSig){}
