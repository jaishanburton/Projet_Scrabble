#include "header_proj.h"


void sauvegardePartie(char Plato[15][15][2],t_joueur player[4],int *nbJoueurs,t_lettre pioche[27])
{
    FILE *fichierJoueur;
    FILE *fichierPlateau;
    FILE *fichierPioche;

    fichierJoueur=fopen("joueurs.dat","wb");
    fichierPlateau=fopen("plateauSave.dat","wb");
    fichierPioche=fopen("pioche.dat","wb");

    if(fichierPlateau==NULL || fichierJoueur==NULL  ||fichierPioche==NULL )
    {
        printf("\nErreur chargement fichier");
    }
    else
    {

        fwrite(Plato, sizeof(char),450,fichierPlateau);
        fwrite(nbJoueurs, sizeof(int),1,fichierJoueur);
        fwrite(player, sizeof(t_joueur),(*nbJoueurs),fichierJoueur);
        fwrite(pioche,sizeof(t_lettre),27,fichierPioche);

        /*for(i=0; i<15; i++)
        {
            for(j=0; j<15; j++)
            {
                for(k=0; k<2; k++)
                {
                    fprintf(fichierPlateau,"%c",Plato[i][j][k]);  //sauvegarde du plateau
                }
            }
        }*/

    }
    fclose(fichierJoueur);
    fclose(fichierPlateau);
    fclose(fichierPioche);
}

void chargementPartie(char plato[15][15][2],t_joueur player[4],int *nbJoueurs,t_lettre pioche[27])
{
    FILE *fichierJoueur;
    FILE *fichierPlateau;
    FILE *fichierPioche;

    fichierJoueur=fopen("joueurs.dat","rb");
    fichierPlateau=fopen("plateauSave.dat","rb");
    fichierPioche=fopen("pioche.dat","rb");

    if(fichierPlateau==NULL || fichierJoueur==NULL  ||fichierPioche==NULL )
    {
        printf("\nErreur chargement fichier");
    }
    else
    {

        fread(plato, sizeof(char),450,fichierPlateau);
        fread(nbJoueurs, sizeof(int),1,fichierJoueur);
        fread(player, sizeof(t_joueur),(*nbJoueurs),fichierJoueur);
        fread(pioche,sizeof(t_lettre),27,fichierPioche);

    }
    fclose(fichierJoueur);
    fclose(fichierPlateau);
    fclose(fichierPioche);
}

int demande_sauvegarde() // sous programme permettant de demander à l'utilisateur s'il veut sauvegarder la partie quitté ou pas à travers l'évènementielle
{
    int i=0;
    char touche;
    int choix_Joueur=0;

    gotoligcol(LIGNEPLATEAU,COLONNEPLATEAU);
    printf("Voulez-vous sauvegarder la partie:\n");
    gotoligcol(LIGNEPLATEAU+1,COLONNEPLATEAU);
    printf(">non<");
    gotoligcol(LIGNEPLATEAU+2,COLONNEPLATEAU);
    printf(" oui ");

    while(touche!=ENTER)    // tant que la touche appuyé sur le clavier n'est pas "entrée"
    {
        curseurOFF();
        if(kbhit())         // si une touche est saisie
        {
            touche=getch(); // récupération de  la touche saisie
            switch(touche)
            {
            case FLBAS:
                i++;      // si on souhaite descendre (i=i+1)
                i%=2;      // deux lignes (première ligne le "oui", deuxième ligne "non")
                break;

            case FLHAUT:
                i--;   // si on souhaite monter ( i=i-1 )
                if(i<0)
                    i=1;
                i%=2;
                break;

            case ENTER:
                choix_Joueur=i%2; // l'utilisateur choisit la ligne en appuyant la touche "entrée"
                break;

            }
            gotoligcol(LIGNEPLATEAU+1+(i%2),COLONNEPLATEAU); // Les 4 premières lignes de code permettant de pointer notre curseur vers ce que nous voulons choisir (soit oui, soit non)
            printf(">");            // 1ère colonne et déplacement sur les deux lignes
            gotoligcol(LIGNEPLATEAU+1+(i%2),COLONNEPLATEAU+4);  // 3ère colonne et déplacement sur les deux lignes
            printf("<");

            gotoligcol(LIGNEPLATEAU+2-(i%2),COLONNEPLATEAU); // Les 4  premières lignes de code permettant de montrer que le curseur n'est pas pointé sur soit "oui",soit "non"
            printf(" ");
            gotoligcol(LIGNEPLATEAU+2-(i%2),COLONNEPLATEAU+4);
            printf(" ");

            gotoligcol(LIGNEPLATEAU+4,COLONNEPLATEAU);
        }

    }
    return choix_Joueur; // Choix du joueur retourner au prg appelant par un booléen valeur 1 pour oui, valeur 0 pour non
}



