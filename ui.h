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

/*
 * cmdGenererArbre
 * Fonction demandant si il faut utiliser le .DICO existant ou en faire un nouveau 
 * <a> : Arbre de mots que l'on veut génerer
 * <*nomFichier> : Nom du fichier 
 */
int cmdGenererArbre(Arbre *a, char *nomFichier);

/* 
 * switchCmdLettre
 * Appel des fonctions suite à la commande rentrée par l'utilisateur.
 * <*a> : Arbre de mots que l'on veut étudier
 * <*nomFichier> : Fichier avec l'arbre
 * <*cmd> Commande choisie r l ou s ... 
 * <*motSuivant> est pour la recherche
 */
void switchCmdLettre(Arbre *a, char *nomFichier, char cmd, unsigned char *motSuivant);

/*
 * printHelp
 * Fonction permettant d'écrire l'aide aux commandes
 */
void printHelp();

/*
 * printMenu
 * Fonction permettant d'afficher le menu
 */
void printMenu();

#endif