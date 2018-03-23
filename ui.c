/*
 * ui.c
 * Fonctions de gestion de l'interface utilisateurs (commandes et affichages)
 * 
 * Auteur : Myriam ANIK et Nicolas SENECAL
 * IMAC1 - TD01 - Promotion 2020
 * Date : 26/03/2018
 */

#include "ui.h"

int cmdGenererArbre(Arbre *a, char *nomFichier) {
  if (strlen(nomFichier) == 0)
    return 0;
  int resGeneration;
  char nomFichierDico[MAX_CHAR] = "";
  char cmd;
  strcat(nomFichierDico, nomFichier);
  strcat(nomFichierDico, ".DICO");

  /* On essaye de générer l'arbre a partir du fichier .DICO */
  resGeneration = genereArbreDico(a, nomFichierDico);
  /* Si le .DICO existe et est non vide, on demande a l'utilisateur s'il veut l'utiliser */
  if (resGeneration > 0) {
    do {
      printf("Un .DICO de ce fichier, contenant %d mots, existe dejà, voulez vous l'utiliser (O/n) ? ", resGeneration);
      scanf(" %c", &cmd);
    } while (cmd != 'O' && cmd != 'o' && cmd != 'N' && cmd != 'n');
  }
  /* Si aucun .DICO existe ou que l'utilisateur ne veut pas l'utiliser */
  if (resGeneration <= 0 || cmd == 'n' || cmd == 'N') {
    freeArbre(*a);
    *a = NULL;
    resGeneration = genereArbreTexte(a, nomFichier);
  }
  switch (resGeneration) {
    case -1:
      printf("Impossible d'ouvrir le fichier \"%s\" !\n", nomFichier);
      return 0;
      break;
    case 0:
      printf("Le fichier \"%s\" est vide !\n", nomFichier);
      return 0;
      break;
    default:
      printf("Le fichier a généré %d mot(s) dans l'arbre lexicographique!\n", resGeneration);
  }
  return 1;
}

void switchCmdLettre(Arbre *a, char *nomFichier, char cmd, unsigned char *motSuivant) {
  switch (cmd) {
    case 'l': /* commande "-l" : affiche les mots du lexique du fichier <nomFichier> en ordre alphabétique ainsi que leurs occurences */
      printf("Mots du lexique :\n");
      afficheDico(*a);
      break;

    case 's': /* commande "-s" : sauvegarde les mots du lexique du fichier <nomFichier> en ordre alphabétique ainsi que leurs occurences dans un fichier .L */
      strcat(nomFichier, ".L");
      if (sauvegardeLexique(*a, nomFichier) != -1)
        printf("Mots du lexique sauvegardé dans '%s'\n", nomFichier);
      else
        printf("Erreur lors de la création du fichier '%s'\n", nomFichier);
      break;

    case 'r': /* commande "-r" : indique si Mot apparaît dans le fichier <nomFichier> */
      if (motSuivant == NULL) { /* si aucun mot n'est indiqué après -r, on demande de l'entrer */
        unsigned char tmp[MAX_CHAR];
        printf("Mot a rechercher : ");
        scanf(" %51s", tmp);
        motSuivant = tmp;
      }
      int nbOccurence = recherche(*a, motSuivant);

      if (nbOccurence == -1)
        printf("Le mot \"%s\" n'est pas présent dans le fichier %s\n", motSuivant, nomFichier);
      else
        printf("Le mot \"%s\" a été trouvé %d fois dans le fichier %s\n", motSuivant, nbOccurence, nomFichier);
      break;

    case 'S': /* commande "-S" : sauvegarde l'arbre dans un fichier .DICO */
      /* Au cas où <nomFichier> est un .DICO, on vide l'arbre et on le reconstruit à partir du fichier contenant le texte */
      freeArbre(*a);
      *a = NULL;
      genereArbreTexte(a, nomFichier);
      strcat(nomFichier, ".DICO");
      if (sauvegardeArbre(*a, nomFichier) != -1)
        printf("Arbre sauvegardé dans '%s'\n", nomFichier);
      else
        printf("Erreur lors de la création du fichier '%s'\n", nomFichier);
      break;

    case 'd': /* commande "-d" : sauvegarde l'arbre en version .dot */
      strcat(nomFichier, ".dot");
      if (genereDot(*a, nomFichier) != -1) {
        printf("Arbre sauvegardé dans '%s'\n", nomFichier);
        printf("Pour générer un pdf de ce fichier, utiliser la commande :\n");
        printf("\tdot -Tpdf %s -o %s.pdf -Gcharset=latin1\n", nomFichier, nomFichier);
      } else
        printf("Erreur lors de la création du fichier '%s'\n", nomFichier);
      break;
  }
}