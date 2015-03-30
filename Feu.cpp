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
#include "Constantes.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

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
    shmdt(NULL);
    exit(0);
}


static void initialisation(int mem, int semFeux)
{
    memoire_partagee = (int*) shmat(mem, NULL, 0);
    //Direction du handler de fin de tache
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_handler = fin_tache;
    sigaction(SIGUSR2, &action, NULL);
    //initialisation des fragments de mémoire partagée
    memoire_partagee[INDICE_ETAT_FEU_NS]= VERT;
    memoire_partagee[INDICE_ETAT_FEU_EO] = ROUGE;
    memoire_partagee[INDICE_TEMPS_NS] = DUREE_INIT_NS;
    memoire_partagee[INDICE_TEMPS_EO] = DUREE_INIT_EO;
    //initailisation des variables statiques
    dureeNS = DUREE_INIT_NS;
    dureeEO = DUREE_INIT_EO;
    etatNS = VERT;
    etatEO = ROUGE;
    tempsNS = DUREE_INIT_NS;
    tempsEO = DUREE_INIT_NS + 5;
    //Mises à jour de l'affichage
    Effacer(COULEUR_AXE_NS);
    Afficher(COULEUR_AXE_NS, "Vert");
    Effacer(COULEUR_AXE_EO);
    Afficher(COULEUR_AXE_EO, "Rouge", GRAS,INVERSE);
}

static void moteur(int semFeux)
{
    struct sembuf reserver = {0, -1, 0};
    struct sembuf liberer = {0, 1, 0};
    for(;;)
    {
        //Quand une temporisation arrive à 0, on passe dans l'état suivant
        if (tempsNS==0)
        {
            switch(etatNS){
                case VERT:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[INDICE_ETAT_FEU_NS] = ORANGE;
                    semop (semFeux, &liberer, 0);
                    etatNS = ORANGE;
                    tempsNS = 3;
                    Effacer (COULEUR_AXE_NS);
                    Afficher(COULEUR_AXE_NS, "Orange",GRAS,INVERSE);
                    break;
                case ORANGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[INDICE_ETAT_FEU_NS] = ROUGE;
                    semop (semFeux, &liberer, 0);
                    etatNS = ROUGE;
                    tempsNS = dureeEO + 7;
                    //7= 2s de rouge + 3s de orange + 2s de rouge en commun
                    //Mise à jour de l'affichage 
                    Effacer(COULEUR_AXE_NS);
                    Afficher(COULEUR_AXE_NS, "Rouge",GRAS,INVERSE);
                    break;
                case ROUGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[INDICE_ETAT_FEU_NS] = VERT;
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
                    memoire_partagee[INDICE_ETAT_FEU_EO] = ORANGE;
                    semop (semFeux, &liberer, 0);
                    etatEO = ORANGE;
                    tempsEO = 3;
                    Effacer (COULEUR_AXE_EO);
                    Afficher(COULEUR_AXE_EO, "Orange",GRAS,INVERSE);
                    break;
                case ORANGE:
                    semop (semFeux, &reserver, 0);
                    memoire_partagee[INDICE_ETAT_FEU_EO] = ROUGE;
                    semop (semFeux, &liberer, 0);
                    etatEO = ROUGE;
                    tempsEO = dureeNS + 7;
                    Effacer(COULEUR_AXE_EO);
                    Afficher(COULEUR_AXE_EO, "Rouge",GRAS,INVERSE);
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
        //Mise à jour de l'affichage
        Afficher(TEMPS_AXE_NS, tempsNS--);
        Afficher(TEMPS_AXE_EO, tempsEO--);
        //Lecture des durées en mémoire
        semop (semFeux, &reserver, 0);
        dureeNS = memoire_partagee[INDICE_TEMPS_NS];
        dureeEO = memoire_partagee[INDICE_TEMPS_EO];
        semop (semFeux, &liberer, 0);
        //Mise à jour de l'affichage
        Effacer(DUREE_AXE_NS);
        Afficher(DUREE_AXE_NS, dureeNS);
        Afficher(DUREE_AXE_EO, dureeEO);
        //On boucle toute les secondes
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

