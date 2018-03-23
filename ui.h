/*
 * ui.h
 * Déclarations des fonctions de gestion de l'interface utilisateurs (commandes et affichages)
 * 
 * Auteur : Myriam ANIK et Nicolas SENECAL
 * IMAC1 - TD01 - Promotion 2020
 * Date : 26/03/2018
 */

#ifndef UI_H
#define UI_H

#include "fichier.h"

int cmdGenererArbre(Arbre *a, char *nomFichier);

/*motSuivant est pour la recherche*/
void switchCmdLettre(Arbre *a, char *nomFichier, char cmd, unsigned char *motSuivant);


#endif