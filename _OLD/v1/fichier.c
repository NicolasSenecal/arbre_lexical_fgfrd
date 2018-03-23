/*
 * fichier.c
 * Fonctions de gestions des fichiers (L, .DICO ...)
 */

#include "fichier.h"

int genereLexiqueTexte(Arbre *a, char *nomIn) {
  FILE* fichier = fopen(nomIn, "r");
  if (fichier == NULL) /* impossible d'ouvrir le fichier */
    return -1;
  char mot[MAX_CHAR];
  int nbMot = 0;

  while (fscanf(fichier, "%51s", mot) != EOF)
    nbMot += ajouteMot(a, mot);

  fclose(fichier); /* on ferme le fichier */
  return nbMot;
}

int sauvegardeLexiqueTexte(Arbre a, char *nomOut) {
  FILE* fichier = fopen(nomOut, "w");
  if (fichier == NULL) /* impossible d'écrire dans le fichier */
    return -1;

  char buffer[MAX_CHAR];
  sauvegardeLexiqueTexteAux(a, fichier, buffer, 0);

  fclose(fichier); /* on ferme le fichier */
  return 1;
}

void sauvegardeLexiqueTexteAux(Arbre a, FILE *out, char *buffer, int indice) {
  if (a == NULL)
    return;
  buffer[indice] = a->lettre;
  if (buffer[indice] == '\0') {
    fprintf(out, "%s : %d\n", buffer, a->occurrence);
  } else {
    buffer[indice] = a->lettre;
    sauvegardeLexiqueTexteAux(a->filsg, out, buffer, indice + 1);
  }
  sauvegardeLexiqueTexteAux(a->frered, out, buffer, indice);
}