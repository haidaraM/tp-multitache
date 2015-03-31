/*************************************************************************
                           Audio  -  description
                             -------------------
    début                : Audio
    copyright            : (C) Audio par Audio
    e-mail               : Audio
*************************************************************************/

//---------- Réalisation de la tâche <Audio> (fichier Audio.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <fmod.hpp>
#include <signal.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
//------------------------------------------------------ Include personnel

#include "Audio.h"
#include "fmod_errors.h"
#include "Outils.h"
#include "Constantes.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
/** Objet système : variable qui nous servira à définir les paramètres de la librairie fmod **/
static FMOD::System *system_audio;
/** Tableau de pointeurs sur les sons initialisés **/
static FMOD::Sound ** sons;

static int memoire_partagee;
static int * m_data;
static int semaphore;

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
static void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        string error_msg = FMOD_ErrorString(result);
        //cout <<"FMOD error ("<<result<<") "<<FMOD_ErrorString(result)<<endl;
        Effacer(MESSAGE);
        Afficher(MESSAGE, error_msg.c_str());
        exit(-1);
    }
}



static void finTache(int num)
{
    FMOD_RESULT result;
    for (int i = 0; i < NB_SONS; ++i) {
        if(sons[i] != NULL)
        {
            result = sons[i]->release();
            ERRCHECK(result);
        }
    }
    delete[] sons;
    result = system_audio->close();
    ERRCHECK(result);

    result=system_audio->release();
    ERRCHECK(result);
    shmdt(m_data);
    exit(0);
}

static void loadSound()
{
    FMOD_RESULT result;
    FMOD::Sound *son;
    // chargement du son generateur
    string rep_generateur = REPERTOIRE_SON + SOUND_GENERATEUR;
    result=system_audio->createSound(rep_generateur.c_str(),FMOD_CREATESAMPLE,NULL,&son);
    sons[INDICE_SOUND_GENERATEUR] = son;
    ERRCHECK(result);

    string rep_car_start = REPERTOIRE_SON + SOUND_CAR_START;
    result=system_audio->createSound(rep_car_start.c_str(),FMOD_SOFTWARE|FMOD_2D|FMOD_CREATESTREAM,NULL,&son);
    sons[INDICE_SOUND_CART_START] = son;
    ERRCHECK(result);

    string rep_duree = REPERTOIRE_SON + SOUND_DUREE;
    result=system_audio->createSound(rep_duree.c_str(),FMOD_CREATESAMPLE,NULL,&son);
    sons[INDICE_SOUND_DUREE] = son;
    ERRCHECK(result);

    string rep_timer = REPERTOIRE_SON + SOUND_TIMER;
    result=system_audio->createSound(rep_timer.c_str(),FMOD_SOFTWARE|FMOD_2D|FMOD_CREATESTREAM,NULL,&son);
    sons[INDICE_SOUND_TIMER] = son;
    ERRCHECK(result);


}

static void initialisation (int memoire)
{

    FMOD_RESULT result;
    result=FMOD::System_Create(&system_audio);
    ERRCHECK(result);

    result=system_audio->init(NB_SONS,FMOD_INIT_NORMAL,0);
    ERRCHECK(result);

    sons = new FMOD::Sound*[NB_SONS];
    for (int i = 0; i < NB_SONS; ++i)
    {
        sons[i] = NULL;
    }
    loadSound();
    memoire_partagee = memoire;

    struct sigaction fin_tache;
    fin_tache.sa_flags = 0;
    fin_tache.sa_handler = finTache;
    sigemptyset(&fin_tache.sa_mask);
    sigaction(SIGUSR2,&fin_tache, NULL);
    m_data =(int*) shmat(memoire_partagee,(void*)0,0);
    Afficher(MESSAGE,"Init ok");
}



static void playSound(int index)
{
    FMOD_RESULT res;
    res=system_audio->playSound(FMOD_CHANNEL_FREE,sons[index],false,NULL);
    ERRCHECK(res);
}


static void moteur()
{

    struct sembuf reserver = {0, -1, 0};
    struct sembuf liberer = {0, 1, 0};
    for(;;)
    {
        /* accès generateur */
        semop(semaphore,&reserver,1);
        int gen = m_data[MEMOIRE_GENERATEUR];
        m_data[MEMOIRE_GENERATEUR] = 0;
        semop(semaphore,&liberer,1);
        if(gen == 1)
            playSound(INDICE_SOUND_GENERATEUR);

        /* accès cmd manuel */
        semop(semaphore,&reserver,1);
        int car = m_data[MEMOIRE_CAR_STAR];
        m_data[MEMOIRE_CAR_STAR] = 0;
        semop(semaphore,&liberer,1);
        if(car == 1)
            playSound(INDICE_SOUND_CART_START);

        /* accès cmd duree */
        semop(semaphore,&reserver,1);
        int d = m_data[MEMOIRE_DUREE];
        m_data[MEMOIRE_DUREE] = 0;
        semop(semaphore,&liberer,1);
        if(d == 1)
            playSound(INDICE_SOUND_DUREE);

        /* accès timer */
        semop(semaphore,&reserver,1);
        int t = m_data[MEMOIRE_TIMER];
        m_data[MEMOIRE_TIMER] = 0;
        semop(semaphore,&liberer,1);
        if(t == 1)
            playSound(INDICE_SOUND_TIMER);
    }
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Audio(int mem)
{
    initialisation(mem);
    moteur();
}