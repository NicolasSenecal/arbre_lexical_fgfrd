/*
 * fichier.c
 * Fonctions de gestions des fichiers (L, .DICO ...)
 */

#include "fichier.h"

int genereArbreTexte(Arbre *a, char *nomIn) {
  FILE* fichier = fopen(nomIn, "r");
  if (fichier == NULL) /* impossible d'ouvrir le fichier */
    return -1;
  unsigned char mot[MAX_CHAR];
  int nbMot = 0;

  while (fscanf(fichier, "%51s", mot) != EOF)
    nbMot += ajouteMot(a, mot);

  fclose(fichier); /* on ferme le fichier */
  return nbMot;
}

int genereArbreDico(Arbre *a, char *nomIn) {
  FILE* fichier = fopen(nomIn, "r");
  if (fichier == NULL) /* impossible d'ouvrir le fichier */
    return -1;

  unsigned char buffer[MAX_CHAR];
  int nbMot = 0;
  int i = 0;

  while (fscanf(fichier, "%c", &(buffer[i])) != EOF) {
    if (buffer[i] == ' ') {
      buffer[i] = '\0';
      nbMot += ajouteMot(a, buffer);
    } else if (buffer[i] == '\n')
      i--;
    else
      i++;
  }

  fclose(fichier); /* on ferme le fichier */
  return nbMot;
}

int sauvegardeLexique(Arbre a, char *nomOut) {
  FILE* fichier = fopen(nomOut, "w");
  if (fichier == NULL) /* impossible d'écrire dans le fichier */
    return -1;

  unsigned char buffer[MAX_CHAR];
  sauvegardeLexiqueAux(a, fichier, buffer, 0);

  fclose(fichier); /* on ferme le fichier */
  return 1;
}

void sauvegardeLexiqueAux(Arbre a, FILE *out, unsigned char *buffer, int indice) {
  if (a == NULL)
    return;
  buffer[indice] = a->lettre;
  if (buffer[indice] == '\0') {
    fprintf(out, "%s : %d \n", buffer, a->occurrence);
  } else {
    buffer[indice] = a->lettre;
    sauvegardeLexiqueAux(a->filsg, out, buffer, indice + 1);
  }
  sauvegardeLexiqueAux(a->frered, out, buffer, indice);
}

int sauvegardeArbre(Arbre a, char *nomOut) {
  FILE* fichier = fopen(nomOut, "w");
  if (fichier == NULL) /* impossible d'écrire dans le fichier */
    return -1;
  sauvegardeArbreAux(a, fichier);
  fclose(fichier); /* on ferme le fichier */
  return 1;
}

void sauvegardeArbreAux(Arbre a, FILE *out) {
  if (a == NULL) {
    fprintf(out, "\n");
    return;
  }
  if (a->lettre == '\0') {
    fprintf(out, " ");
  } else {
    fprintf(out, "%c", a->lettre);
    sauvegardeArbreAux(a->filsg, out);
  }
  sauvegardeArbreAux(a->frered, out);
}

int genereDot(Arbre a, char *nomOut) {
  FILE* fichier = fopen(nomOut, "w");
  if (fichier == NULL) /* impossible d'écrire dans le fichier */
    return -1;

  fprintf(fichier, "digraph arbre {\n  node [shape=circle, height=.5, fontsize=16, splines=ortho];\n");
  ecrireArbreDot(fichier, a);
  fprintf(fichier, "\n}\n");
  fclose(fichier);
  return 1;
}

void ecrireArbreDot(FILE *stream, Arbre a) {
  if (a == NULL)
    return;
  /* Gestion des caractère spéciaux */
  switch (a->lettre) {
    case '\0':
      fprintf(stream, "n%p [label=\"\\\\0\"];\n", a);
      break;
    case '"':
      fprintf(stream, "n%p [label=\"\\\\0\"];\n", a);
      break;
    default:
      fprintf(stream, "n%p [label=\"%c\"];\n", a, a->lettre);
      break;
  }
  if (a->filsg) {
    fprintf(stream, "n%p -> n%p;\n", a, a->filsg);
    ecrireArbreDot(stream, a->filsg);
  }
  if (a->frered) {
    fprintf(stream, "n%p -> n%p [rankdir=LR];\n", a, a->frered);
    fprintf(stream, "{rank=same; n%p, n%p };\n", a, a->frered);
    ecrireArbreDot(stream, a->frered);
  }
}
