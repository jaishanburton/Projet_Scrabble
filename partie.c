#include "header_proj.h"


void partie(int choiceMenu) //Sous programme lançant une partie de SCRABBLE
{

    //varaible nécessaire pour le fonctionnement d'une partie
    t_joueur player[4]; //Un tableau stockant les joueurs
    t_lettre pioche[27]; // tableau stockant la pioche
    char plato[15][15][2]; //Plateau stockant les lettres et les cases
    int nbJoueurs=0,i=0; //Var stockant le nb de joueur et un compteur
    int choixJoueur=5; //Stockage du choix du joueur i
    int findutour; //stock la fin du tour d'un joueur (initialisé comme faux au debut de chaque tour de boucle)


    //Switch permettant d'initialisé les données du jeu
    switch(choiceMenu)
    {
    case 1: //Dans le cas 1 initialise de nouvelles données
        initialisation_Nouvelle_Partie(player,pioche,plato,&nbJoueurs);
        break;
    case 2: //Dans le cas 2 charge les données depuis un les fichiers
        chargementPartie(plato,player,&nbJoueurs,pioche);
        break;
    }
    curseurOFF();
    do //Faire boucle tant que dcondition de fin de jeu ne sont pas verifie
    {
        findutour=0; //Le joueur n'as pas joué
        //affichage du plateau
        affichagePlateauDeJeu(plato);
        //Affichage menu joueur
        gotoligcol(LIGNEMENU,COLONNEMENU);
        printf("%s - %d: ",player[i].name,i+1);
        printf("[");
        for(int h=0; h<6; h++)
        {

            printf(" %c ",player[i].chevalet[h]);

        }
        printf("]");
        gotoligcol(LIGNEMENU+2,COLONNEMENU);
        printf("1 - Poser un mot");
        gotoligcol(LIGNEMENU+3,COLONNEMENU);
        printf("2 - Piocher une lettre");
        gotoligcol(LIGNEMENU+4,COLONNEMENU);
        printf("3 - Passer votre tour");
        gotoligcol(LIGNEMENU+5,COLONNEMENU);
        printf("4 - Quitter la partie");
        do
        {
            fflush(stdin);
            scanf("%d",&choixJoueur);
        }
        while((choixJoueur<1)||(choixJoueur>4));

        //effacage du menu
        gotoligcol(LIGNEMENU,COLONNEMENU);
        printf("                                ");
        gotoligcol(LIGNEMENU+1,COLONNEMENU);
        printf("                                ");
        gotoligcol(LIGNEMENU+2,COLONNEMENU);
        printf("                                ");
        gotoligcol(LIGNEMENU+3,COLONNEMENU);
        printf("                                ");
        gotoligcol(LIGNEMENU+4,COLONNEMENU);
        printf("                                ");
        gotoligcol(LIGNEMENU+5,COLONNEMENU);
        printf("                                ");
        gotoligcol(LIGNEMENU,COLONNEMENU);

        //Selon le choix du joueur
        switch(choixJoueur)
        {
        case 1: //Poser un mot
            gotoligcol(LIGNESAISIT,COLONNESAISIT);
            printf("Vous avez fait le choix de poser un mot:\n");
            effacerSaisitJoueur();
            if(poserUnMot(&player[i],plato)==1)
            {
                if(verifPiocheVide(pioche)!=1)
                {
                    piocherLettre(pioche,player[i].chevalet);
                }
                findutour=1;
            }
            else
            {
                gotoligcol(LIGNESAISIT,COLONNESAISIT);
                printf("Mot implacable! Verifier votre saisit");
                printf("[A P P U Y E R   S U R   U N E   T O U C H E   P O U R   C O N T I N U E R]");
                getch();
                effacerSaisitJoueur();
            }
            break;
        case 2: //Piocher de nouvelles lettre
            // blindage si pioche vide
            if(verifPiocheVide(pioche)!=1)
            {
                printf("                                ");
                retirerLettre(player[i].chevalet,pioche);
                piocherLettre(pioche,player[i].chevalet);
                findutour=1;
            }
            else
            {
                gotoligcol(LIGNESAISIT,COLONNESAISIT);
                printf("La pioche est vide! Faites une autre action!");
                printf("[A P P U Y E R   S U R   U N E   T O U C H E   P O U R   C O N T I N U E R]");
                getch();
                effacerSaisitJoueur();
            }
            break;
        case 3:
            gotoligcol(LIGNESAISIT,COLONNESAISIT);
            printf("Vous avez fait le choix de passer votre tour...\n");
            Sleep(2000);
            effacerSaisitJoueur();
            affichageTableauJoueur(player,nbJoueurs);
            findutour=1;
            break;
        case 4:
            system("cls");
            Sleep(1500);
            gotoligcol(LIGNEPLATEAU,COLONNEPLATEAU);
            printf("Vous avez quitte la partie...");
            Sleep(1500);
            gotoligcol(LIGNEPLATEAU,COLONNEPLATEAU);
            printf("                                               ");
            if(demande_sauvegarde()==1)
            {
                sauvegardePartie(plato,player,&nbJoueurs,pioche);
            }
            curseurOFF();
            system("cls");
            Sleep(1500);
            gotoligcol(LIGNEPLATEAU,COLONNEPLATEAU+5);
            printf("-------------RESULTATS DE LA PARTIE-------------\n");
            affichageTableauJoueur(player,nbJoueurs);
            gotoligcol(LIGNEPLATEAU+nbJoueurs*4,COLONNEPLATEAU);
            printf("[A P P U Y E R   S U R   U N E   T O U C H E   P O U R   C O N T I N U E R]");
            getch();
            break;
        }
        if(choixJoueur!=4 && findutour==1) //Si le joueur a joué mais n'a pas quitté
        {
            i++; //Joueur suivant
            i%=nbJoueurs; //Joueur suivant selon le nombre de joueur dans le partie
        }
    }
    while((choixJoueur!=4) || (verifChevaletsJoueurs(player)!=0 && verifPiocheVide(pioche)==1)); //||(pioche1==0)||((choixJoueur!=4)&&(pioche1==0)));
}

