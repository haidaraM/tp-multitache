/*************************************************************************
                           Feu  -  description
                             -------------------
    début                : Feu
    copyright            : (C) Feu par Feu
    e-mail               : Feu
*************************************************************************/

//---------- Réalisation de la tâche <Feu> (fichier Feu.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "Feu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int* memoire_partagee;
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

static void fin_tache(int numerosignal)
{
    //TODO : je sais plus s'il ya des trucs à faire ou pas
    exit(0);
}


static void initialisation(int *mem)
{
    memoire_partagee = mem;

    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_handler=fin_tache;
    sigaction(SIGUSR2, &action, NULL);
}

static void moteur()
{
    for(;;)
    {

    }
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Feu(int * ptrSharedMemory)
// Algorithme :
//
{
    initialisation(ptrSharedMemory);
    moteur();
} //----- fin de Nom

