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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "Heure.h"
#include "errno.h"
#include "GestionMenu.h"
#include "Generateur.h"

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
	
	//Lancement de l'application
	InitialiserApplication(XTERM);
	//Création de la file de Message
	key_t privatekey = ftok("./TP-Multitache/Carrefour", 'a');
	int fileVoitures = msgget(privatekey, 0770|IPC_CREAT);
	if (errno == EACCES)
	{
		Afficher(MESSAGE, "Erreur EACCES à la création de la file");
	}
	else if (errno == EEXIST)
	{
		Afficher(MESSAGE, "Erreur EEXIST à la crétion de la file");
	}
	else if (errno == ENOENT)
	{
		Afficher(MESSAGE, "Erreur ENOENT à la crétion de la file");
	}
	else if (errno == ENOMEM)
	{
		Afficher(MESSAGE, "Erreur ENOMEM à la création de la file");
	}
	else if (errno == ENOSPC)
	{
		Afficher(MESSAGE, "Erreur ENOSPC à la création de la file");
	}
	else
	{
		Afficher (MESSAGE, fileVoitures);
	}

	//les pid des taches filles 
	pid_t pidHeure, pidMenu, pidGenerateur;
	
	//Création de la tache Heure
	pidHeure = CreerEtActiverHeure();

	//Création de la tache Générateur
	pidGenerateur = CreerEtActiverGenerateur(0, fileVoitures);
	Afficher(MESSAGE, pidGenerateur);
	//Simulation de la pĥase moteur		
	//sleep(10);
	if((pidMenu=fork())==0)
	{
		// TODO : me donner le pid du generateur
		GestionMenu(pidGenerateur);
	}
	else
	{
		while(waitpid(pidMenu, 0, 0)==-1 && errno==EINTR)
		{
		waitpid(pidMenu, 0, 0);
		}
		terminer(pidHeure, pidGenerateur, fileVoitures);
		return 0;
	}
	
}
void terminer(pid_t pidHeure, pid_t pidGenerateur, int fileVoitures )
{
	kill(pidGenerateur, SIGUSR2);
	waitpid(pidGenerateur, 0, 0);
	//envoi de sigusr2 à heure : commande de kill
	kill( pidHeure , SIGUSR2);
	//waitpid
	waitpid(pidHeure, 0, 0);
	//Destruction de la file de Messages
	msgctl(fileVoitures, IPC_RMID, 0);
	TerminerApplication();
}

void masquage(int noSig){}
