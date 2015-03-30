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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "Heure.h"
#include "GestionMenu.h"
#include "Generateur.h"
#include "Voie.h"
#include "Feu.h"
#include "Constantes.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static pid_t les_voies[NB_VOIES];
static int etatFeux;
static int semFeux;
static int fileVoitures;
static pid_t pid_feu;
static pid_t pidHeure;
static pid_t pidGenerateur;
static pid_t pidMenu;

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
int main (void) {
	key_t publickey = ftok(REFERENCE, 'a');

	//handler de masquage
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &action, NULL); // masquage du Ctl+C
	sigaction(SIGCHLD, &action, NULL);// masquage du signal de mort d'un fils
	sigaction(SIGUSR2, &action, NULL);// masquage de SIGUSR2

	//Lancement de l'application
	InitialiserApplication(XTERM);

	//Création de la file de Message
	fileVoitures = msgget(publickey, 0770 | IPC_CREAT);
	if (errno == EACCES) {
		Afficher(MESSAGE, "Erreur EACCES à la création de la file");
	}
	else if (errno == EEXIST) {
		Afficher(MESSAGE, "Erreur EEXIST à la crétion de la file");
	}
	else if (errno == ENOENT) {
		Afficher(MESSAGE, "Erreur ENOENT à la crétion de la file");
	}
	else if (errno == ENOMEM) {
		Afficher(MESSAGE, "Erreur ENOMEM à la création de la file");
	}
	else if (errno == ENOSPC) {
		Afficher(MESSAGE, "Erreur ENOSPC à la création de la file");
	}
	else {
		//Afficher (MESSAGE, fileVoitures);
	}

	//Création du sémaphore de protection de la mémoire partagée
	semFeux = semget(publickey, 1, IPC_CREAT);

	//Création du fragment de mémoire partagé pour a gestion des Feux
	etatFeux = shmget(publickey,4*sizeof(int),0770|IPC_CREAT);

	//Création de la tache Heure
	pidHeure = CreerEtActiverHeure();

	//Création de la tache Générateur
	pidGenerateur = CreerEtActiverGenerateur(0, fileVoitures);

	// TODO : completer la création des feux si c'est pas bon
	if((pid_feu=fork())==0)
	{// Fille
		Feu(etatFeux, semFeux);
	}
	else
	{ // mere
		for (unsigned int i = 0; i < NB_VOIES; ++i)
		{
			les_voies[i] = fork();
			if(les_voies[i] == 0)
			{// fille
				Voie(fileVoitures,semFeux,etatFeux,(TypeVoie)(i+1));
			}
		}
		if ((pidMenu = fork()) == 0)
		{// Fille
			GestionMenu(pidGenerateur, fileVoitures, etatFeux);
		}
		else
		{// mere
			waitpid(pidMenu, 0, 0);
			terminer();
			return 0;
		}
	}
}
void terminer()
{
	// Destruction des voies
	for(unsigned int i =0; i<NB_VOIES; i++)
	{
		kill(les_voies[i], SIGUSR2);
		waitpid(les_voies[i],0,0);
	}

	// destruction des feux
	kill(pid_feu,SIGUSR2);
	waitpid(pid_feu,0,0);

	kill(pidGenerateur, SIGCONT); // On reveille le generateur au cas ou il etait suspendu
	kill(pidGenerateur, SIGUSR2);
	waitpid(pidGenerateur, 0, 0);

	//envoi de sigusr2 à heure : commande de kill
	kill( pidHeure , SIGUSR2);
	waitpid(pidHeure, 0, 0);

	//Destruction de la file de Messages
	msgctl(fileVoitures, IPC_RMID, 0);

	// destruction de la memoire partagée
	shmctl(etatFeux,IPC_RMID,0);

	//Destuction du sémaphore pour la mémoire memFeux
	semctl(semFeux, 0, IPC_RMID, 0);
	TerminerApplication();
}
