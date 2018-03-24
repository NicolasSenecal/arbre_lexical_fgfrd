/*
 * fichier.c
 * Fonctions de gestions des fichiers pour les arbres binaire lexicaux (L, .DICO ...)
 * 
 * Auteur : Myriam ANIK et Nicolas SENECAL
 * IMAC1 - TD01 - Promotion 2020
 * Date : 26/03/2018
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


void printHelp(){
  printf("\033[H\033[2J");

  printf(" _____________ \n");
  printf("** AFFICHAGE **\n");
  printf(" _____________ \n");
  printf("Pour afficher les mots du fichier en ordre alphabétique il suffit de taper : \033[35;01m./Lexique -l votrefichier\033[00m\n");
  printf(" _____________ \n");
  printf("** SAUVEGARDE **\n");
  printf(" _____________ \n");
  printf("Pour sauvegarde les mots du lexique en ordre alphabétique ainsi que leurs occurences dans un fichier .L  taper :\033[35;01m ./Lexique -s votrefichier\033[00m\n \n");
  printf(" _____________ \n");
  printf("** RECHERCHE **\n ");
  printf(" _____________ \n"); 
  printf("Pour rechercher un mot dans un fichier taper : \033[34;01m \033[35;01m ./Lexique -r votremot\033[00m\n \n ");
  printf(" _____________ \n");
  printf("** SAUVEGARDE DICO ** \n");
  printf(" _____________ \n");
  printf("Pour sauvegarder votre fichier en .DICO taper : \033[35;01m ./Lexique -S votrefichier\033[00m\n \n");
  printf(" _____________ \n");
  printf("** AFFICHAGE DOT **\n");
  printf(" _____________ \n");
  printf("Pour visualiser votre fichier en .DOT taper : \033[35;01m ./Lexique -d votrefichier\033[00m\n\n");
  printf("** MENU **\n");
  printf(" _____________ \n");
  printf("Pour être guidé par un menu, il suffit de taper \033[35;01m ./Lexique  \033[00m\n\n");

}
