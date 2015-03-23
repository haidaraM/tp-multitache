/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : 19/03/2015
    copyright            : (C) 2015 par Mohamed HAIDARA
    e-mail               : mohamed.haidara@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Voie> (fichier Voie.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/msg.h>

//------------------------------------------------------ Include personnel
#include "Voie.h"
#include "Voiture.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static std::vector<pid_t > les_deplacements;
static int file_voitures;
static TypeVoie type_voie;


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

static void finTache(int numero_signal)
{
    for(unsigned int i = 0; i<les_deplacements.size(); i++)
    {
        kill(SIGUSR2,les_deplacements[i]);
        waitpid(les_deplacements[i],0,0);
    }
    exit(0);
}

static void finFils(int numero_signal)
{
    // Synchro de fin avec n'importe quel fils
    //TODO : enlever le fils du vecteur
    pid_t pid_t1 = waitpid(-1,0,0);
}

static void initialisation()
{
    // TODO : Ignorer les signaux
    // création des handlers
    struct sigaction fin_tache, fin_fils;
    fin_tache.sa_flags = 0;
    fin_tache.sa_handler = finTache;
    sigemptyset(&fin_tache.sa_mask);

    fin_fils.sa_flags = 0;
    fin_fils.sa_handler = finFils;
    sigemptyset(&fin_fils.sa_mask);

    // Armement des handler
    sigaction(SIGUSR2,&fin_tache, NULL);
    sigaction(SIGCHLD, &fin_fils, NULL);
}


void Moteur()
{
    // TODO : penser à la mise à de la zone Voiture pour la derniere voiture arrivée

    for(;;)
    {
        sleep(1);
        MsgVoiture nouvelleCaisse;
        int res = msgrcv(file_voitures,&nouvelleCaisse,TAILLE_MSG_VOITURE-sizeof(long),type_voie,IPC_NOWAIT);
        if(res != -1)
        {

            Effacer(MESSAGE);
            Afficher(MESSAGE, "Retrait ok");
        }

    }
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Voie (int fileVoitures, TypeVoie typeVoie)
// Algorithme :
//
{
    //TODO : recuperer memoire partagée pour les états des feux
    file_voitures = fileVoitures;
    type_voie = typeVoie;
    initialisation();
    Moteur();
} //----- fin de Void


