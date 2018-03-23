/*
 * fichier.h
 * Déclaration des fonctions de gestions des fichiers (L, .DICO ...)
 */
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

void sauvegardeArbreAux(Arbre a, FILE *out);

int genereDot(Arbre a, char *nomOut);

void ecrireArbreDot(FILE *stream, Arbre a);