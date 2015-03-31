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
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>

using namespace std;
//------------------------------------------------------ Include personnel
#include "Voie.h"
#include "Voiture.h"
#include "Constantes.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static list<pid_t> les_deplacements;
static int file_voitures;
static TypeVoie type_voie;
static int semaphore_feu;
static int shared_memory_id;
static int * data;

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

//static void finTache ( int numero_signal )
// Mode d'emploi : Handler de fin d'application quand l'utilisateur appuie sur Q
//
// Contrat :
//
// Algorithme : On parcourt la liste des taches Deplacement encore présents et on les
// tue.
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
    // detachement  de la mémoire
    shmdt(data);
    exit(0);
} //----- fin de finTache



//static void finFils ( int numero_signal )
// Mode d'emploi : Handler de fin de déplacement d'une tache fille Deplacement
//
// Contrat :
//
// Algorithme : On recupère le pid du fils qui vient de mourrir on l'enleve de la liste
//
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
} //----- fin de finFils



//static void initialisation ( int fileVoitures,int sem,int shmid, TypeVoie typeVoie)
// Mode d'emploi : Initialise les valeurs indispensables à la tache. Crée les handler
//
// Contrat :
//
// Algorithme
static void initialisation(int fileVoitures,int sem,int shmid, TypeVoie typeVoie)
{
    file_voitures = fileVoitures;
    type_voie = typeVoie;
    semaphore_feu = sem;
    shared_memory_id = shmid;

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

    // attachement à la memoire partagée
    data =(int*) shmat(shared_memory_id,(void*)0,SHM_RDONLY);
} //----- fin de initialisation


//void moteur ()
// Mode d'emploi : Phase moteur de la tache qui l'arrivée des voitures sur le carrefour
void moteur()
{
    int res;

    struct sembuf reserver = {0, -1, 0};
    struct sembuf liberer = {0, 1, 0};
    for(;;)
    {
        MsgVoiture nouvelleCaisse;
        do{
             res = (int) msgrcv(file_voitures,&nouvelleCaisse,TAILLE_MSG_VOITURE,type_voie,0);
        } while(res == -1 && errno == EINTR);

        unsigned int num = nouvelleCaisse.uneVoiture.numero;
        TypeVoie entree = nouvelleCaisse.uneVoiture.entree;
        TypeVoie sortie = nouvelleCaisse.uneVoiture.sortie;

        DessinerVoitureFeu(num,entree ,sortie);
        OperationVoie(MOINS,entree);

        semop(semaphore_feu,&reserver,1);
        int NS = data[INDICE_ETAT_FEU_NS];
        int EO = data[INDICE_ETAT_FEU_EO];
        semop(semaphore_feu,&liberer,1);

        switch(entree)
        {
            case NORD:
            case SUD:
                while(NS == ORANGE || NS == ROUGE)
                {
                    sleep(1); // lecture toute les secondes
                    semop(semaphore_feu,&reserver,1);
                    NS = data[INDICE_ETAT_FEU_NS];
                    semop(semaphore_feu,&liberer,1);
                }
                break;
            case EST:
            case OUEST:
                while(EO == ORANGE || EO == ROUGE)
                {
                    sleep(1); // lecture toute les secondes
                    semop(semaphore_feu,&reserver,1);
                    EO = data[INDICE_ETAT_FEU_EO];
                    semop(semaphore_feu,&liberer,1);
                }
                break;
            default:
                break;
        }
        // lancement du deplacement
        pid_t voiture = DeplacerVoiture(num,entree,sortie);
        // ajout à la liste
        les_deplacements.push_back(voiture);
    }
} //--------- fin de moteur

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Voie (int fileVoitures,int sem,int shmid, TypeVoie typeVoie)
// Algorithme :
//
{
    initialisation(fileVoitures,sem,shmid,typeVoie);
    moteur();
} //----- fin de Voie


