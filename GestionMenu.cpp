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
#include <errno.h>
#include <sys/shm.h>
#include <stdio.h>

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
static bool etat_generateur = false;
static unsigned int numero_voiture = 0;
static pid_t pid_generateur;
static int file_voitures;
static int shared_memory_id;

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


static void initialisation(pid_t generateur, int fileVoitures, int shmid)
{
    file_voitures = fileVoitures;
    pid_generateur = generateur;
    shared_memory_id = shmid;
}

static void moteur()
{
    for(;;)
    {
        Menu();
    }
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GestionMenu(pid_t generateur, int fileVoitures, int shmid)
// Algorithme :
//
{
    initialisation(generateur,fileVoitures, shmid);
    moteur();
} //----- fin de Nom

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

}

void Commande ( TypeVoie entree, TypeVoie sortie )
{

    numero_voiture = (numero_voiture % 200) + 1;
    Voiture voiture = {entree, sortie, numero_voiture};
    MsgVoiture msgVoiture = {entree,voiture};
    // Affichage de la dernière voiture
    Afficher(NUMERO,numero_voiture,GRAS);
    Afficher(ENTREE,entree, GRAS);
    Afficher(SORTIE,sortie, GRAS);
    int resultat;
    do{
        resultat = msgsnd(file_voitures,&msgVoiture,TAILLE_MSG_VOITURE,IPC_NOWAIT);
    } while(resultat == -1 && errno == EINTR);
}

void Commande ( TypeVoie voie, unsigned int duree )
{
    // TODO : utiliser un semphore
    // attachement
    int * data =(int*) shmat(shared_memory_id,(void*)0,0);

    if(voie == NORD || voie == SUD)
        data[INDICE_TEMPS_NS] = duree;
    else if(voie == EST || voie == OUEST)
        data[INDICE_TEMPS_EO] = duree;

    // detachement
    shmdt(data);
}
