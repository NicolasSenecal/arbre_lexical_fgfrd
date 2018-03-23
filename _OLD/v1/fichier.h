/*
 * fichier.h
 * Déclaration des fonctions de gestions des fichiers (L, .DICO ...)
 */
#include "arbre.h"

/*
 * genereLexiqueTexte
 * Construit un arbre lexical depuis un fichier texte
 * TO DO (retourne -1 si erreur ou le nb de mot ajouté sans compté les doublons)
 */
int genereLexiqueTexte(Arbre *a, char *nomIn);

int sauvegardeLexiqueTexte(Arbre a, char *nomOut);

void sauvegardeLexiqueTexteAux(Arbre a, FILE *out, char *buffer, int indice);