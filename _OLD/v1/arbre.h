/*
 * arbre.h
 * Déclaration de la structure d'arbre binaire lexical sous forme fils gauhe/frère droit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 51 /* Nombre maximal de lettre par mot ('\0' compris) */

typedef struct noeud {
  unsigned char lettre;
  struct noeud *filsg, *frered;
  int occurrence; /* Nombre d'occurrences du mot si le noeud contient son caractère de fin '\0' */
} Noeud, *Arbre;

/* 
 * alloueNoeud
 * Alloue un noeud de l'arbre lexical dans l'espace mémoire et initialise ses attributs
 * Quitte le programme en cas d'erreur d'allocation
 * <lettre> : unsigned char de la lettre contenue dans le noeud
 * Retourne un pointeur sur le noeud
 */
Arbre alloueNoeud(unsigned char lettre);

/*
 * freeArbre
 * Libère l'espace mémoire occupé par un arbre
 * <a> : L'arbre a libérer
 */
void freeArbre(Arbre a);

/*
 * ajouteBranche
 * Ajoute un mot sous forme d’une liste de fils gauche, s’arrête quand rencontre un '\0'
 * <*a> : Pointeur sur l'arbre (début de la nouvelle branche)
 * <*mot> : Pointeur sur la première lettre du mot a ajouter
 */
void ajouteBranche(Arbre *a, char *mot);

/*
 * ajouteMot
 * Permet d'ajouter un mot dans l'arbre s'il n'y est pas, incrémente son nombre d'occurrence dans le cas contraire
 * <*a> : Pointeur sur l'arbre 
 * <*mot> : Pointeur sur la première lettre du mot a ajouter
 * retourne 1 si le mot a bien été ajouté ou 0 s'il est dejà présent dans l'abre
 */
int ajouteMot(Arbre *a, char *mot);

/*
 * recherche
 * Vérifie l'existance d'un mot dans l'arbre
 * <a> : L'arbre dans lequel nous recherchons un mot
 * <*mot> : Pointeur sur la première lettre du mot a chercher
 * retourne 1 si le mot est présent, 0 sinon
 */
int recherche(Arbre a, char *mot);

void afficheDico(Arbre a);

void afficheDicoAux(Arbre a, char *buffer, int indice);