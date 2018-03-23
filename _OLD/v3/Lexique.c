/*
 * 
 */

#include "fichier.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {/* Aucune commandes */
    printf("Usage : ./Lexique [-l] [-r <Mot>] [-s] [-S] [-d] nomFichier[.DICO]\n");
    return 0;
  }

  int i, resGeneration;
  char cmd;
  char *nomFichier = argv[argc - 1];
  char nomFichierDico[MAX_CHAR] = "";
  char nomFichierLexique[MAX_CHAR] = "";
  char nomFichierDot[MAX_CHAR] = "";
  strcat(nomFichierLexique, nomFichier);
  strcat(nomFichierLexique, ".L");
  strcat(nomFichierDico, nomFichier);
  strcat(nomFichierDico, ".DICO");
  strcat(nomFichierDot, nomFichier);
  strcat(nomFichierDot, ".dot");

  Arbre a = NULL;
  /* On essaye de générer l'arbre a partir du fichier .DICO */
  resGeneration = genereArbreDico(&a, nomFichierDico);
  /* Si le .DICO existe et est non vide, on demande a l'utilisateur s'il veut l'utiliser */
  if (resGeneration > 0) {
    do {
      printf("Un .DICO de ce fichier, contenant %d mots, existe dejà, voulez vous l'utiliser (O/n) ? ", resGeneration);
      scanf(" %c", &cmd);
    } while (cmd != 'O' && cmd != 'o' && cmd != 'N' && cmd != 'n');
  }
  /* Si aucun .DICO existe ou que l'utilisateur ne veut pas l'utiliser */
  if (resGeneration <= 0 || cmd == 'n' || cmd == 'N') {
    freeArbre(a);
    a = NULL;
    resGeneration = genereArbreTexte(&a, nomFichier);
  }
  switch (resGeneration) {
    case -1:
      printf("Impossible d'ouvrir le fichier \"%s\" !\n", nomFichier);
      break;
    case 0:
      printf("Le fichier \"%s\" est vide !\n", nomFichier);
      break;
    default:
      printf("Le fichier a généré %d mot(s) dans l'arbre lexicographique!\n", resGeneration);
  }

  for (i = 1; i < argc - 1; i++) {
    if (*argv[i] == '-') {
      switch (*(argv[i] + 1)) { /* Pointeur sur l'adresse du caractère suivant de argv[i] */
        case 'l': /* commande "-l" : affiche les mots du lexique du fichier <nomFichier> en ordre alphabétique ainsi que leurs occurences */
          printf("Mots du lexique :\n");
          afficheDico(a);
          break;
        case 's': /* commande "-s" : sauvegarde les mots du lexique du fichier <nomFichier> en ordre alphabétique ainsi que leurs occurences dans un fichier .L */
          if (sauvegardeLexique(a, nomFichierLexique) != -1)
            printf("Mots du lexique sauvegardé dans '%s'\n", nomFichierLexique);
          else
            printf("Erreur lors de la création du fichier '%s'\n", nomFichierLexique);
          break;
        case 'r': /* commande "-r" : indique si Mot apparaît dans le fichier <nomFichier> */
          if (++i >= argc) { /* si aucun mot n'est indiqué après -r */
            printf("Veuillez indiquer un mot pour votre recherche/n");
            return 1;
          }
          int nbOccurence = recherche(a, (unsigned char*) argv[i]);
          if (nbOccurence == -1)
            printf("Le mot \"%s\" n'est pas présent dans le fichier %s\n", argv[i], nomFichier);
          else
            printf("Le mot \"%s\" a été trouvé %d fois dans le fichier %s\n", argv[i], nbOccurence, nomFichier);
          break;
        case 'S': /* commande "-S" : sauvegarde l'arbre dans un fichier .DICO */
          if (sauvegardeArbre(a, nomFichierDico) != -1)
            printf("Arbre sauvegardé dans '%s'\n", nomFichierDico);
          else
            printf("Erreur lors de la création du fichier '%s'\n", nomFichierDico);
          break;
        case 'd': /* commande "-d" : sauvegarde l'arbre en version .dot */
          if (genereDot(a, nomFichierDot) != -1) {
            printf("Arbre sauvegardé dans '%s'\n", nomFichierDot);
            printf("Pour générer un pdf de ce fichier, utiliser la commande :\n");
            printf("\tdot -Tpdf %s -o %s.pdf -Gcharset=latin1\n", nomFichierDot, nomFichierDot);
          } else
            printf("Erreur lors de la création du fichier '%s'\n", nomFichierDot);
          break;
      }
    }
  }

  freeArbre(a);

  return 0;
}