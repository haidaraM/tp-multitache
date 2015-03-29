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
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
//------------------------------------------------------ Include personnel
#include "Feu.h"
#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
const int DUREE_INIT_NS = 20;
const int DUREE_INIT_EO = 10;
const int ROUGE = 0;
const int ORANGE = 1;
const int VERT = 2;
//------------------------------------------------------------------ Types


//---------------------------------------------------- Variables statiques
static int dureeNS;
static int dureeEO;
static int etatNS;
static int etatEO;
static int tempsNS;
static int tempsEO;
int * memoire_partagee;
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
    exit(0);
}


static void initialisation(int mem, int semFeux)
{
    memoire_partagee = (int*) shmat(mem, NULL, 0);

    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_handler=fin_tache;
    sigaction(SIGUSR2, &action, NULL);
    memoire_partagee[0]= VERT;
    memoire_partagee[1] = ROUGE;
    memoire_partagee[2] = DUREE_INIT_NS;
    memoire_partagee[3] = DUREE_INIT_EO;
    dureeNS = DUREE_INIT_NS;
    dureeEO = DUREE_INIT_EO;
    etatNS = VERT;
    etatEO = ROUGE;
    tempsNS = DUREE_INIT_NS;
    tempsEO = DUREE_INIT_NS + 5;
    Effacer(COULEUR_AXE_NS);
    Afficher(COULEUR_AXE_NS, "Vert");
    Effacer(COULEUR_AXE_EO);
    Afficher(COULEUR_AXE_EO, "Rouge");
}

static void moteur(int semFeux)
{
    struct sembuf reserver = {0, -1, 0};
    struct sembuf liberer = {0, 1, 0};
    for(;;)
    {
        if (tempsNS==0)
        {
            switch(etatNS){
                case VERT:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[0] = ORANGE;
                    semop (semFeux, &liberer, 0);
                    etatNS = ORANGE;
                    tempsNS = 3;
                    Effacer (COULEUR_AXE_NS);
                    Afficher(COULEUR_AXE_NS, "Orange");
                    break;
                case ORANGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[0] = ROUGE;
                    semop (semFeux, &liberer, 0);
                    etatNS = ROUGE;
                    tempsNS = dureeEO + 7;
                    Effacer(COULEUR_AXE_NS);
                    Afficher(COULEUR_AXE_NS, "Rouge");
                    break;
                case ROUGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[0] = VERT;
                    semop (semFeux, &liberer, 0);
                    etatNS = VERT;
                    tempsNS = dureeNS;
                    Effacer(COULEUR_AXE_NS);
                    Afficher(COULEUR_AXE_NS, "Vert");
                    break;
            }
        }

        if (tempsEO==0)
        {
            switch(etatEO){
                case VERT:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[1] = ORANGE;
                    semop (semFeux, &liberer, 0);
                    etatEO = ORANGE;
                    tempsEO = 3;
                    Effacer (COULEUR_AXE_EO);
                    Afficher(COULEUR_AXE_EO, "Orange");
                    break;
                case ORANGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[1] = ROUGE;
                    semop (semFeux, &liberer, 0);
                    etatEO = ROUGE;
                    tempsEO = dureeNS + 7;
                    Effacer(COULEUR_AXE_EO);
                    Afficher(COULEUR_AXE_EO, "Rouge");
                    break;
                case ROUGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[1] = VERT;
                    semop (semFeux, &liberer, 0);
                    etatEO = VERT;
                    tempsEO = dureeEO;
                    Effacer(COULEUR_AXE_EO);
                    Afficher(COULEUR_AXE_EO, "Vert");
                    break;
            }
        }
        Afficher(TEMPS_AXE_NS, tempsNS--);
        Afficher(TEMPS_AXE_EO, tempsEO--);
        semop (semFeux, &liberer, 0);
        dureeNS = memoire_partagee[2];
        dureeEO = memoire_partagee[3];
        semop (semFeux, &liberer, 0);
        Effacer(DUREE_AXE_NS);
        Afficher(DUREE_AXE_NS, dureeNS);
        Afficher(DUREE_AXE_EO, dureeEO);
        sleep(1);
    }
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Feu(int SharedMemory, int semFeux)
// Algorithme :
//
{
    initialisation(SharedMemory, semFeux);
    moteur(semFeux);
} //----- fin de Nom

