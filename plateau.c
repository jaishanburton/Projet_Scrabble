#include "header_proj.h"

void initialisationPlateaudeJeu(char plato[15][15][2])
{
    int i,j;
    FILE * fichier;

    fichier=fopen("plateau.txt","r");

    while (!(feof(fichier)))
    {
        for(i=0; i<15; i++)
        {
            for(j=0; j<15; j++)
            {
                fscanf(fichier,"%c",&plato[i][j][0]);
                plato[i][j][1]='0';
            }
        }
    }
    fclose(fichier);
}

/*
    2=§
    3=&
    4=@
    5=%
    6=#
*/


void affichagePlateauDeJeu(char plato[15][15][2])
{
// 1 case = 1 trait + 1 espace + 1er caractere points + espace + soit lettre soit espace + espace + trait pr fermer case
    int i,j,k,l;
    system("cls");
    initialisationPlateaudeJeu(plato);
    for(i=0; i<29; i++) //Ligne
    {
        for(j=0; j<15; j++)        //affichage Ligne caractere
        {

            for(k=0; k<7; k++)
            {
                gotoligcol(LIGNEPLATEAU+i,COLONNEPLATEAU+k+(j*6));
                Color(15,0);
                if(i%2==0)
                {
                    if(k%7==0)
                    {
                        printf("%c",0xB3);
                    }
                    else if(k%7==1)
                    {
                        printf(" ");
                    }
                    else if(k%7==2)
                    {
                        switch(plato[i/2][j][0])
                        {

                        case '2' :
                            Color(2,0);
                            printf("%c",0x15);
                            break;
                        case '3' :
                            Color(12,0);
                            printf("%c",0x26);
                            break;
                        case '4' :
                            Color(9,0);
                            printf("%c",0x40);
                            break;
                        case '5' :
                            Color(6,0);
                            printf("%c",0x25);
                            break;
                        case '6' :
                            Color(5,0);
                            printf("%c",0x23);
                            break;
                        }
                    }
                    else if(k%7==4)
                    {
                        if(plato[i/2][j][1]!='0')
                            printf("%c",plato[i/2][j][1]);
                    }
                    else if(k%7==6|| k%7==0)
                    {
                        printf("%c",0xB3);
                    }
                    else if(k%7==3 || k%7==1 || k%7==5)
                    {
                        printf(" ");
                    }

                    else if(k%7==5)
                    {
                        printf(" ");
                    }

                }
                else if(i%2==1)
                {
                    if(k==0 && j==0)
                    {
                        printf("%c",0xC3);
                    }
                    else if(k==6 && j==14)
                    {
                        printf("%c",0xB4);
                    }
                    else if(k%7==0)
                    {
                        printf("%c",0xC5);
                    }
                    else
                    {
                        printf("%c",0xC4);
                    }
                }
            }
            printf("\n");

        }

    }
    for(l=COLONNEPLATEAU; l<=(COLONNEPLATEAU+90); l++)
    {

        if(l==COLONNEPLATEAU)
        {
            gotoligcol(LIGNEPLATEAU-1,l);
            printf("%c",0xDA);
            gotoligcol(LIGNEPLATEAU+29,l);
            printf("%c",0xC0);
        }
        else if(l==COLONNEPLATEAU+90)
        {
            gotoligcol(LIGNEPLATEAU-1,l);
            printf("%c",0xBF);
            gotoligcol(LIGNEPLATEAU+29,l);
            printf("%c",0xD9);

        }
        else if((l-COLONNEPLATEAU)%6==0)
        {
            gotoligcol(LIGNEPLATEAU-1,l);
            printf("%c",0xC2);
            gotoligcol(LIGNEPLATEAU+29,l);
            printf("%c",0xC1);
        }
        else
        {
            gotoligcol(LIGNEPLATEAU-1,l);
            printf("%c",0xC4);
            gotoligcol(LIGNEPLATEAU+29,l);
            printf("%c",0xC4);
        }

    }
}




