/*************************************************************************
                           Menu.h  -  description
                             -------------------
    début                : 23 Jan 2015
    copyright            : (C) 2015 par Mathieu Maranzana
    e-mail               : Mathieu.Maranzana@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Menu> (fichier Menu.h) -----------------
#if ! defined MENU_H
#define MENU_H

//------------------------------------------------------------------------
// rôle du module <Menu>
//    ce module est en charge de la gestion du menu (interface homme-machine)
//    de l'application multitâche gérant la circulation sur le carrefour
//    les commandes autorisées sont :
//      1. q|Q : déclenche la fin de l'application
//      2. g|G : permet la suspension ou la réactivation de la tâche
//               <Générateur> (arrivée automatique de voitures)
//      3. m|M : engendre manuellement l'arrivée d'une voiture au carrefour
//               (arrivée manuelle d'une voiture)
//      4. d|D : permet de changer la durée du feu vert de l'un des 2 axes
//               (axe N-S ou axe E-O)
//    ce module se charge aussi de la mise à jour de l'écran du TP
//    (zone <Commande> et <Message>)
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////// INCLUDE
//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

/////////////////////////////////////////////////////////////////// PUBLIC
//---------------------------------------------------- Fonctions publiques
void Menu ( void );
// mode d'emploi :
//    - commandes autorisées en minuscule ou majuscule :
//      1. q|Q : déclenche la fin de l'application
//      2. g|G : permet la suspension ou la réactivation de la tâche
//               <Générateur> (arrivée automatique de voitures)
//      3. m|M : engendre manuellement l'arrivée d'une voiture au
//               carrefour (arrivée manuelle d'une voiture)
//      4. d|D : modifie la durée du feu vert de l'un des 2 axes
//               (axe N-S ou axe E-O)
//      Toute autre commande génère une erreur (affichage d'un message)
//      et déclenche une nouvelle saisie
//      Pour les commandes licites, la procédure <Menu> appelle la procédure
//      <Commande> en respectant la convention suivante pour les paramètres
//      => interfaçage possible avec le menu :
//        1. q|Q : code = 'Q' (prototype simple)
//        2. g|G : code = 'G' (prototype simple)
//        3. m|M : voie d'entrée, voie de sortie (prototype complexe)
//        4. d|D : voie, durée du feu (prototype complexe)
//      => les prototypes imposés de <Commande> sont donc les suivants :
//        a.  void Commande ( char code );
//        b.  void Commande ( TypeVoie entree, TypeVoie sortie );
//            (cas de l'arrivée manuelle)
//        c.  void Commande ( TypeVoie voie, unsigned int duree );
//            (cas du changement de durée d'un feu vert)
//    - le menu travaille en BOUCLE INFINIE et la seule manière d'en sortir
//      est l'option 1. (quitter), c'est à dire la frappe de la touche 'q'
//      ou 'Q'
//
// contrat : aucun
//

#endif // MENU_H

