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
#include <list>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/msg.h>

using namespace std;
//------------------------------------------------------ Include personnel
#include "Voie.h"
#include "Voiture.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static list<pid_t> les_deplacements;
static int file_voitures;
static TypeVoie type_voie;
static int semaphore_feu;

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
    // Masque de SIGUSR2
    struct sigaction action;
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    sigaction(SIGCHLD, &action, NULL);
    list<pid_t>::iterator it ;
    for(it = les_deplacements.begin(); it != les_deplacements.end(); it++)
    {
        kill(*it,SIGUSR2);
        waitpid(*it,0,0);
    }
    exit(0);
}

static void finFils(int numero_signal)
{
    // Synchro de fin avec n'importe quel fils
    pid_t fils = waitpid(-1,0,0);
    list<pid_t>::iterator it;
    int done = false;
    for(it = les_deplacements.begin(); it!=les_deplacements.end() && !done; ++it)
    {
        if(fils == *it)
        {
            done = true;
            it=les_deplacements.erase(it);
        }
    }
}

static void initialisation(int fileVoitures,int sem, TypeVoie typeVoie)
{
    file_voitures = fileVoitures;
    type_voie = typeVoie;
    semaphore_feu = sem;
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


void moteur()
{
    // TODO : penser à la mise à de la zone Voiture pour la derniere voiture arrivée
    // TODO : Mettre à jour la liste des voitures en attente
    // TODO : lecture de la mémoire partagée
    for(;;)
    {
        MsgVoiture nouvelleCaisse;
        int res = (int) msgrcv(file_voitures,&nouvelleCaisse,TAILLE_MSG_VOITURE,type_voie,IPC_NOWAIT);
        if(res != -1)
        {
            unsigned int num = nouvelleCaisse.uneVoiture.numero;
            TypeVoie entree = nouvelleCaisse.uneVoiture.entree;
            TypeVoie sortie = nouvelleCaisse.uneVoiture.sortie;

            Afficher(NUMERO,num,GRAS);
            Afficher(ENTREE,entree, GRAS);
            Afficher(SORTIE,sortie, GRAS);
            /*Effacer(MESSAGE);
            Afficher(MESSAGE, "retrait ok");*/
            pid_t voiture = DeplacerVoiture(num,entree,sortie);
            les_deplacements.push_back(voiture);
        }

    }
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Voie (int fileVoitures,int sem, TypeVoie typeVoie)
// Algorithme :
//
{
    initialisation(fileVoitures,sem,typeVoie);
    moteur();
} //----- fin de Void


