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

//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "unistd.h"
#include "Heure.h"
#include "signal.h"
#include "sys/wait.h"

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
{	
	pid_t pidC;
	InitialiserApplication(XTERM);
	//Création de la tache Heure
	
	
	pidC = CreerEtActiverHeure();
	
	
		
	sleep(10);
	//envoi de sigusr2 à heure : commande de kill
	kill( pidC , SIGUSR2);
	//waitpid
	waitpid(pidC, 0, 0);
	TerminerApplication();
	return 0;
	
	
}
