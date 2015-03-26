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
#include <errno.h>
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "Heure.h"

#include "GestionMenu.h"
#include "Generateur.h"
#include "Voie.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static pid_t les_voies[NB_VOIES];
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
	key_t privatekey = ftok("./TP-Multitache/Carrefour", 'a');
	//Les id des IPC
	int fileVoitures, semFeux;

	//handler de masquage
	struct sigaction action;
	action.sa_handler = masquage;
	sigaction(SIGINT, &action, NULL); // masquage du Ctl+C
	sigaction(SIGCHLD, &action, NULL);// masquage du signal de mort d'un fils
	sigaction(SIGUSR2, &action, NULL);// masquage de SIGUSR2

	//Lancement de l'application
	InitialiserApplication(XTERM);

	//Création de la file de Message
	fileVoitures = msgget(privatekey, 0770 | IPC_CREAT);
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
	semFeux = semget(privatekey, 1, IPC_CREAT);

	//Création du fragment de mémoire partagé pour a gestion des Feux


	//les pid des taches filles 
	pid_t pidHeure, pidMenu, pidGenerateur;

	//Création de la tache Heure
	pidHeure = CreerEtActiverHeure();

	//Création de la tache Générateur
	pidGenerateur = CreerEtActiverGenerateur(0, fileVoitures);
	//Afficher(MESSAGE, pidGenerateur);
	//Simulation de la pĥase moteur		
	//sleep(10);

	// TODO : création des feux
	if ((les_voies[INDICE_VOIE_NORD] = fork()) == 0)
	{ // Fille
		Voie(fileVoitures, NORD);
	}
	else
	{ // Mère
		if ((les_voies[INDICE_VOIE_SUD] = fork()) == 0)
		{// Fille
			Voie(fileVoitures, SUD);
		}
		else
		{//Mere
			if ((les_voies[INDICE_VOIE_EST] = fork()) == 0)
			{// Fille
				Voie(fileVoitures, EST);
			}
			else
			{// Mere
				if ((les_voies[INDICE_VOIE_OUEST] = fork()) == 0)
				{// Fille
					Voie(fileVoitures, OUEST);
				}
				else
				{ // Mere
					if ((pidMenu = fork()) == 0)
					{// Fille
						GestionMenu(pidGenerateur, fileVoitures);
					}
					else
					{
						while(waitpid(pidMenu, 0, 0) == -1 && errno == EINTR);
						terminer(pidHeure, pidGenerateur, fileVoitures, semFeux);
						return 0;
					}
				}
			}
		}

	}
}
void terminer(pid_t pidHeure, pid_t pidGenerateur,int fileVoitures, int semFeux)
{
	for(unsigned int i =0; i<NB_VOIES; i++)
	{
		kill(les_voies[i], SIGUSR2);
		waitpid(les_voies[i],0,0);
		Effacer(MESSAGE);
		Afficher(MESSAGE,"Attente voie");
	}
	Effacer(MESSAGE);
	kill(pidGenerateur, SIGCONT); // On reveille le generateur au cas ou il etait suspendugit p
	kill(pidGenerateur, SIGUSR2);
	waitpid(pidGenerateur, 0, 0);
	//envoi de sigusr2 à heure : commande de kill
	kill( pidHeure , SIGUSR2);
	//waitpid
	waitpid(pidHeure, 0, 0);
	//Destuction du sémaphore pour la mémoire memFeux
	semctl(semFeux, 0, IPC_RMID, 0);
	//Destruction de la file de Messages
	msgctl(fileVoitures, IPC_RMID, 0);
	TerminerApplication();
}

void masquage(int noSig){}
