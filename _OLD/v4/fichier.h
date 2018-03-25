/*
 * fichier.h
 * Déclaration des fonctions de gestions des fichiers pour les arbres binaire lexicaux (L, .DICO ...)
 * 
 * Auteur : Myriam ANIK et Nicolas SENECAL
 * IMAC1 - TD01 - Promotion 2020
 * Date : 26/03/2018
 */

#ifndef FICHIER_H
#define FICHIER_H

#include "arbre.h"

/*
 * genereArbreTexte
 * Construit un arbre lexical depuis un fichier texte
 * TO DO (retourne -1 si erreur ou le nb de mot ajouté sans compté les doublons)
 * Retourne -1 si une erreur est survenue a l'ouverture du fichier
 *          ou alors le nombre de mot ajouté (sans compter les doublons)
 */
int genereArbreTexte(Arbre *a, char *nomIn);

int genereArbreDico(Arbre *a, char *nomIn);

/*
 * sauvegardeLexique
 * Fonction permettant la sauvegarde du lexique dans un fichier
 * <a> : Arbre de mots que l'on veut sauvegarder dans un fichier
 * <*out> : Nom du fichier de sortie (avec le .L)
 * Retourne -1 si une erreur est survenue a l'ouverture du fichier ou 1 sinon
 */
int sauvegardeLexique(Arbre a, char *nomOut);

/*
 * sauvegardeLexiqueAux
 * Fonction auxiliaire permettant la sauvegarde du texte grace à sauvegardeLexiqueTexte
 * <a> : Notre arbre de mots que l'on veut sauvegarder dans un fichier
 * <*out> : Fichier de sortie
 * <*buffer> : Chaine de caractères tampon 
 * <indice> : Indice à partir duquel on commence à tamponner
 */
void sauvegardeLexiqueAux(Arbre a, FILE *out, unsigned char *buffer, int indice);

/*
 * sauvegardeArbre
 * Fonction permettant la sauvegarde du lexique dans un fichier
 * <a> : Arbre de mots que l'on veut sauvegarder dans un fichier
 * <*out> : Nom du fichier de sortie (avec le .DICO)
 * Retourne -1 si une erreur est survenue a l'ouverture du fichier ou 1 sinon
 */
int sauvegardeArbre(Arbre a, char *nomOut);

/*
 * sauvegardeArbreAux
 * Fonction auxiliaire permettant la sauvegarde du lexique dans un fichier
 * <a> : Arbre de mots que l'on veut sauvegarder dans un fichier
 * <*out> : Nom du fichier de sortie (avec le .DICO)
 */
void sauvegardeArbreAux(Arbre a, FILE *out);

/*
 * genereDot
 * Fonction permettant de générer un pdf dot
 * <a> : Arbre de mots que l'on veut traduire en dot
 * <*out> : Nom du fichier en écriture seule 
 */
int genereDot(Arbre a, char *nomOut);


/*
 * ecrireArbreDot
 * Fonction permettant de générer un pdf dot en prenant en compte un arbre
 * <a> : Arbre de mots que l'on veut dessiner en dot
 * <*stream> : Nom du fichier d'écriture
 */
void ecrireArbreDot(FILE *stream, Arbre a);


/*
 * printHelp
 * Fonction permettant d'écrire l'aide aux commandes*/
void printHelp();

#endif