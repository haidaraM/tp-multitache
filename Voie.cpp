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
#include <sys/types.h>
#include <bits/sigaction.h>
#include <signal.h>
#include <sys/wait.h>

//------------------------------------------------------ Include personnel
#include "Voie.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static std::vector<pid_t > les_deplacements;

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
void Voie ()
// Algorithme :
//
{
    //TODO : recuperer boite au lettres
    //TODO : recuperer memoire partagée pour les états des feux

} //----- fin de Void

static void finTache(int numero_signal)
{
    for(int i = 0; i<les_deplacements.size(); i++)
    {
        kill(SIGUSR2,les_deplacements[i]);
        waitpid(les_deplacements[i],0,0);
    }
}

static void finFils(int numero_signal)
{

}

static void initialisation()
{
    // TODO : Ignorer les signaux
    // création des handlers
    sigaction fin_tache, fin_fils;
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

