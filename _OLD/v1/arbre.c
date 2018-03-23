/*
 * arbre.c
 * Déclaration de la structure d'arbre binaire lexical sous forme fils gauhe/frère droit
 */

#include "arbre.h"

Arbre alloueNoeud(unsigned char lettre) {
  Noeud* tmp;
  tmp = (Noeud*) malloc(sizeof (Noeud));
  if (!tmp) {
    printf("Memory run out\n");
    exit(1);
  }
  tmp->lettre = lettre;
  tmp->filsg = NULL;
  tmp->frered = NULL;
  if (lettre == '\0')
    tmp->occurrence = 1;
  else
    tmp->occurrence = 0;
  return tmp;
}

void freeArbre(Arbre a) {
  if (a != NULL) {
    freeArbre(a->filsg);
    freeArbre(a->frered);
    free(a);
  }
}

void ajouteBranche(Arbre *a, char *mot) {
  *a = alloueNoeud(*mot);
  if (*mot != '\0')
    ajouteBranche(&((*a)->filsg), mot + 1);
}

int ajouteMot(Arbre *a, char *mot) {
  if (*a == NULL) { /* si l’arbre est vide, le mot est ajouté sous forme d’une liste de fils (une branche) */
    ajouteBranche(a, mot);
    return 1;
  }
  if ((*a)->lettre < *mot) /* si la lettre du noeud est plus petite que celle du mot on ajoute le mot dans le frere */
    return ajouteMot(&((*a)->frered), mot);
  if ((*a)->lettre == *mot && *mot != '\0') /* si la lettre est trouvée et que la fin du mot n’est pas atteinte, on ajoute le reste du mot dans le fils */
    return ajouteMot(&((*a)->filsg), mot + 1);
  else if ((*a)->lettre > *mot) { /* si la lettre du noeud est suppérieur a celle du mot, on creer une branche et on l'ajoute avant ce noeud */
    Arbre tmp = NULL;
    ajouteBranche(&tmp, mot);
    tmp->frered = *a;
    *a = tmp;
    return 1;
  }
  /* Le mot est dejà présent dans l'arbre */
  (*a)->occurrence++;
  return 0;
}

int recherche(Arbre a, char *mot) {
  if (a == NULL)
    return 0;
  if (*mot < a->lettre) /* si la lettre du mot est inférieure à celle du noeud, le mot n'est pas présent */
    return 0;
  if (*mot == a->lettre) { /* si la lettre est égale a celle du noeud... */
    if (*mot == '\0') /*... et qu'on est a la fin du mot, celui-ci est présent */
      return 1;
    return recherche(a->filsg, mot + 1); /* sinon on continue la recherche dans les fils */
  }
  return recherche(a->frered, mot); /* si la lettre du mot est supérieur à celle du noeud, on continue la recherche dans les frere  */
}

void afficheDico(Arbre a) {
  char buffer[MAX_CHAR];
  afficheDicoAux(a, buffer, 0);
}

void afficheDicoAux(Arbre a, char *buffer, int indice) {
  if (a == NULL)
    return;
  buffer[indice] = a->lettre;
  if (buffer[indice] == '\0') {
    printf("%s : %d\n", buffer, a->occurrence);
  } else {
    afficheDicoAux(a->filsg, buffer, indice + 1);
  }
  afficheDicoAux(a->frered, buffer, indice);
}