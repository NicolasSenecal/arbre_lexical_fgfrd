/*
 * 
 */

#include "fichier.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {/* Aucune commandes */
    printf("Usage : ./Lexique [-l] [-s] [-r <Mot>] [-S] nomFichier[.DICO]\n");
    return 0;
  }

  int i, resGeneration;
  char *nomFichier = argv[argc - 1];
  char nomFichierOut[MAX_CHAR] = "";

  Arbre a = NULL;
  resGeneration = genereLexiqueTexte(&a, nomFichier);
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
          strcat(nomFichierOut, nomFichier);
          strcat(nomFichierOut, ".L");
                    printf("--->%s\n", nomFichierOut);
          sauvegardeLexiqueTexte(a, nomFichierOut);
          printf("Mots du lexique sauvegardé dans '%s'\n", nomFichierOut);
          break;
        case 'S': /* commande "-S" : sauvegarde l'arbre dans un fichier .DICO */
          printf("Arbre sauvegardé dans :\n");
          break;
        case 'r': /* commande "-r" : indique si Mot apparaît dans le fichier <nomFichier> */
          if (++i >= argc) { /* si aucun mot n'est indiqué après -r */
            printf("Veuillez indiquer un mot pour votre recherche/n");
            return 1;
          }
          char *motRecherche = argv[i];
          printf("Recherche du mot :%s\n", motRecherche);
          break;
      }
    }
  }

  freeArbre(a);

  return 0;
}