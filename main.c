#include "header_proj.h"

int main()
{
    //Initialisation curseur invisible
    //Declaration de l'aléatoire
    srand(time(NULL));
    //Variable de choix du menu
    int choix=5;
    // declaration d'un menu
    do  //Blindage menu tant que la condition pour quitter n'est pas vérifier
    {
        curseurOFF();
        do  //Blindage selection tant que le
        {
            system("cls"); //Nettoyage de l'ecran
            printf("----------------SCRABBLE----------------\n");
            printf("1. Lancer une nouvelle partie\n");
            printf("2. Reprendre une partie sauvegardee\n");
            printf("3. Afficher l'aide\n");
            printf("4. Afficher les scores des joueurs\n");
            printf("0. Quitter le jeu\n");
            fflush(stdin);
            scanf("%d",&choix);
        }
        while(choix<0||choix>4);

        system("cls");//Nettoyage de l'ecran

        //choix proposés par le menu
        switch(choix)
        {
        case 1 :
            printf("Vous avez decide de lancer une nouvelle partie.\n");

            /* affichagePlateauDeJeu(plato);
             getch();*/
            partie(choix);
            break;

        case 2 :
            printf("Vous avez decide de reprendre une partie sauvegardee.\n");
            partie(choix);
            break;

        case 3 :
            aide();
            printf("Voici des informations pour vous aider et vous guider :\n");
            break;

        case 4 :
            printf("Voici le score de chacun des joueurs :\n");
            break;

        case 0 :
            printf("Au revoir et a bientot pour de nouvelles parties !\n");
            Sleep(2000);
            break;
        default :
            printf("Votre saisie est erronee.\n");
        }
        system("cls");
    }
    while(choix!=0);

    return 0;
}
