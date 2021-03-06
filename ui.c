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
      printf("Impossible d'ouvrir le fichier \n");
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
  char nomFichierDot[MAX_CHAR] = "";
  char nomFichierL[MAX_CHAR] = "";
        char nomFichierDico[MAX_CHAR] = "";
  switch (cmd) {
    case 'l': /* commande "-l" : affiche les mots du lexique du fichier <nomFichier> en ordre alphabétique ainsi que leurs occurences */
      printf("Mots du lexique :\n");
      afficheDico(*a);
      break;

    case 's': /* commande "-s" : sauvegarde les mots du lexique du fichier <nomFichier> en ordre alphabétique ainsi que leurs occurences dans un fichier .L */
      strcat(nomFichierL, nomFichier);
      strcat(nomFichierL, ".L");
      if (sauvegardeLexique(*a, nomFichierL) != -1)
        printf("Mots du lexique sauvegardé dans '%s'\n", nomFichierL);
      else
        printf("Erreur lors de la création du fichier '%s'\n", nomFichierL);
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
      strcat(nomFichierDico, nomFichier);
      strcat(nomFichierDico, ".DICO");
      if (sauvegardeArbre(*a, nomFichierDico) != -1)
        printf("Arbre sauvegardé dans '%s'\n", nomFichierDico);
      else
        printf("Erreur lors de la création du fichier '%s'\n", nomFichierDico);
      break;

    case 'd': /* commande "-d" : sauvegarde l'arbre en version .dot */
      strcat(nomFichierDot, nomFichier);
      strcat(nomFichierDot, ".dot");
      if (genereDot(*a, nomFichierDot) != -1) {
        printf("Arbre sauvegardé dans '%s'\n", nomFichierDot);
        printf("Pour générer un pdf de ce fichier, utiliser la commande :\n");
        printf("\tdot -Tpdf %s -o %s.pdf -Gcharset=latin1\n", nomFichierDot, nomFichierDot);
      } else
        printf("Erreur lors de la création du fichier '%s'\n", nomFichierDot);
      break;

    case 'h': /* commande "-h" : affiche l'aide */
      printHelp();
      break;
  }
}

void printHelp() {
  printf("\033[H\033[2J");
  printf("Usage : ./Lexique [-l] [-r <Mot>] [-s] [-S] [-d] nomFichier\n\n");

  printf("-- AFFICHAGE :\n");
  printf("\t\033[35;01m-l\033[00m : affiche les mots du fichier en ordre alphabétique\n");

  printf("-- SAUVEGARDE :\n");
  printf("\t\033[35;01m-s\033[00m : sauvegarde les mots du lexique en ordre alphabétique ainsi que leurs occurences dans un fichier .L \n");
  printf("\t\033[35;01m-S\033[00m : sauvegarder l'arbre lexicographique de votre fichier en .DICO \n");
  printf("\t\033[35;01m-d\033[00m : sauvegarder l'arbre lexicographique au format DOT pour pouvoir le visualiser \n");

  printf("-- RECHERCHE : \n");
  printf("\t\033[35;01m-r [<Mot>]\033[00m : rechercher un mot dans l'arbre lexicographique\n");

  printf("-- MENU :\n");
  printf("\tEn l'absence d'option sur la ligne de commande, toutes ces fontionnalités seront accessibles via un menu.\n\n");

}

void printMenu() {
  printf("\n");
  printf("--------------------------\n");
  printf("-----      Menu      -----\n");
  printf("--------------------------\n");
  printf("\n");
  printf("\033[35;01m l \033[00mAfficher les mots du lexique par ordre alphabétique. \n");
  printf("\033[35;01m s \033[00mSauvegarder les mots ordonnés dans un nouveau fichier. \n");
  printf("\033[35;01m r \033[00mRechercher un mot du lexique.  \n");
  printf("\033[35;01m S \033[00mSauvegarder votre lexique en format .DICO.  \n");
  printf("\033[35;01m d \033[00mSauvegarder votre lexique en format .dot. \n");
  printf("\033[35;01m h \033[00mRéafficher le menu\n");
  printf("\033[35;01m q \033[00mQuitter le programme\n");
  printf("\n");
}
