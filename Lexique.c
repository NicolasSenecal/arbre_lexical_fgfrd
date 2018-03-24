/*
 * Lexique.c (main)
 * Programme construisant le lexique d'un texte contenu dans un fichier fournit 
 * comme argument de la ligne de commande, avec différentes options et fonctionnalités
 * 
 * Auteur : Myriam ANIK et Nicolas SENECAL
 * IMAC1 - TD01 - Promotion 2020
 * Date : 26/03/2018
 */

#include "ui.h"

int main(int argc, char *argv[]) {
  int i;
  char cmd[MAX_CHAR] = "";
  char nomFichier[MAX_CHAR] = "";
  char motachercher[MAX_CHAR]="";
  Arbre a = NULL;

  if (argc == 1) {/* Aucune commandes */
    printf("Usage : ./Lexique [-l] [-r <Mot>] [-s] [-S] [-d] nomFichier\n");
    printf("Tapez ./Lexique -h pour l'aide \n");
    int choixMenu;   

    printf("---Menu---\n\n");
    printf("\033[35;01m1.\033[00mAfficher les mots du lexique par ordre alphabétique. \n");
    printf("\033[35;01m2.\033[00mSauvegarder les mots ordonnés dans un nouveau fichier. \n");
    printf("\033[35;01m3.\033[00mRechercher un mot du lexique.  \n");
    printf("\033[35;01m4.\033[00mSauvegarder votre lexique en format .DICO.  \n");
    printf("\033[35;01m5.\033[00mSauvegarder votre lexique en format .Dot. \n");
    printf("\033[35;01m6.\033[00mAfficher l'aide.  \n");
    printf(" Votre choix?\n\n");
    scanf("%d", &choixMenu);

    switch(choixMenu){
      case 1:
        printf("Pour quel fichier souhaitez vous afficher les mots du lexique ? \n");
        scanf("%s",nomFichier);
        while (cmdGenererArbre(&a, nomFichier) == 0) {
          printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
         scanf(" %51s", cmd);
           if (cmd[0] == '0')
         return 0;

         strcpy(nomFichier, cmd);
        }
        switchCmdLettre(&a, nomFichier, 'l', NULL);
      break;

       case 2:
        printf("Quel fichier souhaitez vous sauvegarder en ordonné ? \n");
        scanf("%s",nomFichier);
        while (cmdGenererArbre(&a, nomFichier) == 0) {
          printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
         scanf(" %51s", cmd);
           if (cmd[0] == '0')
         return 0;

         strcpy(nomFichier, cmd);
        }
        switchCmdLettre(&a, nomFichier, 's', NULL);
      break;

       case 3:
       printf("Quel mot voulez-vous chercher  ? \n");
        scanf("%s", motachercher);
        printf("Dans quel fichier souhaitez vous chercher le mot %s \n", motachercher);
        scanf("%s",nomFichier);
        while (cmdGenererArbre(&a, nomFichier) == 0) {
          printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
         scanf(" %51s", cmd);
           if (cmd[0] == '0')
         return 0;

         strcpy(nomFichier, cmd);
        }
         switchCmdLettre(&a, nomFichier, 'r', (unsigned char*) motachercher);
      break;

      case 4:
        printf("Quel fichier souhaitez vous sauvegarder en .DICO ? \n");
        scanf("%s",nomFichier);
        while (cmdGenererArbre(&a, nomFichier) == 0) {
          printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
         scanf(" %51s", cmd);
           if (cmd[0] == '0')
         return 0;

         strcpy(nomFichier, cmd);
        }
        switchCmdLettre(&a, nomFichier, 'S', NULL);
      break;


      case 5:
        printf("Quel fichier souhaitez vous générer en .dot? \n");
        scanf("%s",nomFichier);
        while (cmdGenererArbre(&a, nomFichier) == 0) {
          printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
         scanf(" %51s", cmd);
           if (cmd[0] == '0')
         return 0;

         strcpy(nomFichier, cmd);
        }
        switchCmdLettre(&a, nomFichier, 'd', NULL);
      break;

      case 6:
        printHelp();
      break;

    }



    return choixMenu; 
  } 
  else {
    strcpy(nomFichier, argv[argc - 1]);
  }


 if(strcmp(argv[argc-1],"-h")!=0){
  while (cmdGenererArbre(&a, nomFichier) == 0) {
    printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
    scanf(" %51s", cmd);
    if (cmd[0] == '0')
      return 0;

    strcpy(nomFichier, cmd);
  }

  for (i = 1; i < argc - 1; i++) {
    if (*argv[i] == '-') {
      cmd[0] = *(argv[i] + 1); /* Pointeur sur l'adresse du caractère suivant de argv[i] */
      if (i + 1 >= argc - 1) /* si aucun mot n'est indiqué après la commande */
        switchCmdLettre(&a, nomFichier, cmd[0], NULL);
      else
        switchCmdLettre(&a, nomFichier, cmd[0], (unsigned char*) argv[++i]);
    }
  }

  freeArbre(a);
}
  else{ 
    printHelp();
  }

return 0;

}
