/*************************************************************************
                           GestionMenu  -  description
                             -------------------
    début                : 19/03/2015
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : mohamed.haidara@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <GestionMenu> (fichier GestionMenu.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/sem.h>

//------------------------------------------------------ Include personnel
#include "GestionMenu.h"
#include "Outils.h"
#include "Menu.h"
#include "Voiture.h"
#include "Constantes.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static bool etat_generateur = false; // generateur desactivé au demarrage
static unsigned int numero_voiture = 0;
static pid_t pid_generateur;
static int file_voitures;
static int shared_memory_id;
static int semaphore_feux;

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

//static void initialisation ( pid_t generateur, int fileVoitures, int shmid, int semaphore )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme : Aucun
static void initialisation(pid_t generateur, int fileVoitures, int shmid, int semaphore)
{
    // Recupération des ressources crées par la mère
    file_voitures = fileVoitures;
    pid_generateur = generateur;
    shared_memory_id = shmid;
    semaphore_feux = semaphore;
} //--------- fin de initialisation

static void moteur()
{
    for(;;)
    {
        Menu();
    }
} // ---- fin de moteur

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GestionMenu(pid_t generateur, int fileVoitures, int shmid, int sem)
// Algorithme :
//
{
    initialisation(generateur,fileVoitures, shmid, sem);
    moteur();
} //----- fin de GestionMenu

void Commande ( char code )
{
    switch (code)
    {
        case 'g':
        case 'G':
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
            break;
        }
        case 'q':
        case 'Q':
            exit(0);
        default:
            break;
    }
} // ---- Fin de commande

void Commande ( TypeVoie entree, TypeVoie sortie )
{

    numero_voiture = (numero_voiture % 200) + 1;
    Voiture voiture = {entree, sortie, numero_voiture};
    MsgVoiture msgVoiture = {entree,voiture};
    // Affichage de la dernière voiture
    Afficher(NUMERO,numero_voiture,GRAS);
    Afficher(ENTREE,entree, GRAS);
    Afficher(SORTIE,sortie, GRAS);

    OperationVoie(PLUS,entree);

    int resultat;
    do{
        resultat = msgsnd(file_voitures,&msgVoiture,TAILLE_MSG_VOITURE,IPC_NOWAIT);
    } while(resultat == -1 && errno == EINTR);
} // ---- Fin de commande


void Commande ( TypeVoie voie, unsigned int duree )
{
    // attachement
    int * data =(int*) shmat(shared_memory_id,(void*)0,0);
    struct sembuf reserver = {0, -1, 0};
    struct sembuf liberer = {0, 1, 0};
    if(voie == NORD || voie == SUD)
    {
        semop(semaphore_feux,&reserver,1);
        data[INDICE_TEMPS_NS] = duree;
        semop(semaphore_feux,&liberer,1);
    }
    else if(voie == EST || voie == OUEST)
    {
        semop(semaphore_feux,&reserver,1);
        data[INDICE_TEMPS_EO] = duree;
        semop(semaphore_feux,&liberer,1);
    }
    // detachement
    shmdt(data);
} // ---- Fin de commande
