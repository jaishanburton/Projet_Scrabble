#include "header_proj.h"

void initialisation_Nouvelle_Partie(t_joueur player[4],t_lettre pioche[27],char plato[15][15][2],int *nbJoueurs)
{
    initPioche(pioche);
    initialisationPlateaudeJeu(plato);
    for(int k=0; k<15; k++) // Initialisation seconde dimension (lettres) du plateau de jeu
    {
        for(int h=0; h<15; h++)
        {
            plato[k][h][1]='0';
        }
    }

    printf("saisir le nombre de joueurs:\n");
    do
    {
        fflush(stdin);
        scanf("%d",nbJoueurs);
    }
    while((*nbJoueurs<2)||(*nbJoueurs>4));

    for(int i=0; i<*nbJoueurs; i++)          // initialiser les joueurs
    {

        printf("Saisir le nom du Joueur %d:\n",i);//initialisation player et numero du joueur
        fflush(stdin);
        scanf("%s",(player[i].name));

        player[i].score=0;

        for(int j=0; j<7; j++)
        {
            player[i].chevalet[j]='0';
        }
        piocherLettre(pioche,player[i].chevalet);
    }
}

void aide()
{
    char plato[15][15][2];
    initialisationPlateaudeJeu(plato);
    affichagePlateauDeJeu(plato);
    printf("\n\nVous venez de choisir l'option aide.\n");
    printf("Les regles du jeu sont simples : \n Vous disposez d'un chevalet compose de plusieurs lettres.\n");
    printf("L'objectif est de former des mots avec ces lettres et les placer sur le plateau de jeu.\nCertaines cases vous donneront des bonus suppementaires.\n");
    printf("Vous avez le droit de poser des lettres, piocher des lettres ou bien de passer votre tour.\n");
    getch();
}

void effacerSaisitJoueur()
{
    for(int i=0; i<7; i++)
    {
        gotoligcol(LIGNESAISIT+i,COLONNESAISIT);
        printf("                                                                             \n");
    }
}


void conversionMotMaj(char cara[16])
{
    int i=0;
    while(cara[i]!='\0')
    {
        if( cara[i]>='a' && cara[i]<='z' )
        {
            cara[i]-=32;
        }
        i++;
    }
}
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void gotoligcol(int lig, int col)
{
// ressources
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );

}

void curseurOFF() //fonction permettant d'éteindre le curseur
{
    //Commande eteignant le curseur
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}


void balise1()
{
    system("cls");
    printf("BALISE UNE");
    Sleep(1000);
}

void balise2()
{
    printf("BALISE DEUX");
}

