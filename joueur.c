#include "header_proj.h"


void initInfoJoueur(t_joueur *data)
{
    printf("Saisir le nom d'un joueur:\n");
    fflush(stdin);
    scanf("%s",(data->name));
}

void affichageTableauJoueur(t_joueur player[4],int nbJoueur)
{
    Sleep(500);
    for(int i=0; i<nbJoueur; i++)
    {

        gotoligcol(LIGNEPLATEAU+2+3*i,COLONNEPLATEAU);
        printf("[%d]NOM: %s",i+1,player[i].name);
        Sleep(500);
        gotoligcol(LIGNEPLATEAU+3+3*i,COLONNEPLATEAU);
        printf("SCORE: %d points",player[i].score);
        Sleep(700);
    }
}

