#include "header_proj.h"

//Sous Programme initialisation de la pioche
void initPioche(t_lettre pioche[27])
{
    for(int i=0; i<26; i++) //Boucle parcourant la pioche
    {
        pioche[i].lettre='A'+i;//Assigne chaque jeton lettre à une case de la pioche

        //Conditions permettant d'assigné le nombre de jetons disponible par lettres dans la pioche
        if(pioche[i].lettre=='J' || pioche[i].lettre=='K' || pioche[i].lettre=='Q' || pioche[i].lettre=='W' || pioche[i].lettre=='X' || pioche[i].lettre=='Y'|| pioche[i].lettre=='Z')
        {
            pioche[i].nbRestant=1;
        }
        else if(pioche[i].lettre=='B' || pioche[i].lettre=='C' || pioche[i].lettre=='F' || pioche[i].lettre=='G' || pioche[i].lettre=='H' || pioche[i].lettre=='P' || pioche[i].lettre=='V')
        {
            pioche[i].nbRestant=2;
        }
        else if(pioche[i].lettre=='D' || pioche[i].lettre=='M')
        {
            pioche[i].nbRestant=3;
        }
        else if(pioche[i].lettre=='L')
        {
            pioche[i].nbRestant=5;
        }
        else if(pioche[i].lettre=='N' || pioche[i].lettre=='O' || pioche[i].lettre=='R' || pioche[i].lettre=='S' || pioche[i].lettre=='T' || pioche[i].lettre=='U')
        {
            pioche[i].nbRestant=6;
        }
        else if(pioche[i].lettre=='I')
        {
            pioche[i].nbRestant=8;
        }
        else if(pioche[i].lettre=='A')
        {
            pioche[i].nbRestant=9;
        }
        else if(pioche[i].lettre=='E')
        {
            pioche[i].nbRestant=15;
        }

    }
    pioche[26].lettre='?';//Assigne la derniere case au jeton '?'
    pioche[26].nbRestant=2;//Assigne le nombre de jeton '?' disponible dans la pioche

}

//Sous Programme affichage de la pioche
void affPioche(t_lettre pioche[27])
{
    for(int i=0; i<27 ; i++)
    {
        printf("%c | %d",pioche[i].lettre,pioche[i].nbRestant);
    }
}

void retirerLettre(char chevalet[7],t_lettre pioche[27])
{
    int lettreASuppr[7]= {0,0,0,0,0,0,0};
    char touche;
    int lettreI=0;
    int j;

    gotoligcol(LIGNEMENU,COLONNEMENU);
    printf("Selection des lettres a supprimer");
    gotoligcol(LIGNEMENU+1,COLONNEMENU);
    printf("[FLECHE HAUT] Selection [FLECHE BAS] Deselection");
    gotoligcol(LIGNEMENU+2,COLONNEMENU);
    for(int i=0; i<7; i++)
    {
        printf(" %c ",chevalet[i]);
    }

    gotoligcol(LIGNEMENU+3,COLONNEMENU);
    for(int i=0; i<7; i++)
    {
        if(lettreASuppr[i])
        {
            printf("  ");
        }
        else
        {
            printf(" * ");
        }
    }

    gotoligcol(LIGNEMENU+4,COLONNEMENU);
    for(int i=0; i<lettreI+1; i++)
    {
        if(i==lettreI)
        {
            printf(" ^ ");
        }
        else
        {
            printf("   ");
        }
    }
    while(touche!=27 && touche!=13)
    {
        if(kbhit())
        {
            touche=getch();
            if((int)touche==FLDROITE)
            {
                lettreI++;
                lettreI%=7;
            }
            else if((int)touche==FLGAUCHE)
            {
                lettreI--;
                if(lettreI<0)
                    lettreI+=7;
                lettreI%=7;
            }
            else if((int)touche==FLHAUT)
            {
                lettreASuppr[lettreI]=0;
            }
            else if((int)touche==FLBAS)
            {
                lettreASuppr[lettreI]=1;
            }
            else if((int)touche==13)
            {

                gotoligcol(LIGNEMENU+2,COLONNEMENU);
                for(int i=0; i<7; i++)
                {
                    if(lettreASuppr[i])
                    {
                        j=0;
                        while(chevalet[i]!=pioche[j].lettre)
                        {
                            j++;
                        }
                        pioche[j].nbRestant++;
                        chevalet[i]='0';
                    }
                    printf(" %c ",chevalet[i]);
                }
            }

            gotoligcol(LIGNEMENU+3,COLONNEMENU);
            for(int i=0; i<7; i++)
            {
                if(lettreASuppr[i])
                {
                    printf("   ");
                }
                else
                {
                    printf(" * ");
                }
            }
            gotoligcol(LIGNEMENU+4,COLONNEMENU);
            for(int i=0; i<7; i++)
            {
                if(i==lettreI)
                {
                    printf(" ^ ");
                }
                else
                {
                    printf("   ");
                }
            }
        }

    }
}

//Ssp assignant des lettres au chevalet du joueur
void piocherLettre(t_lettre pioche[27],char chevaletJoueur[7])
{
    int boucle=0; //Boucle de passage dans le chevalet
    int nblettre=0;//Selection d'une lettre
    srand(time(NULL));//Declaration de l'aleatoire
    if(!verifPiocheVide(pioche)) //Si la pioche n'est pas vide
    {
        while(boucle<7) //Tant que la boucle de passage n'atteint pas la denriere case
        {
            if(chevaletJoueur[boucle]=='0') //Si la case i du chevalete est vide
            {
                nblettre=rand()%28;
                while(pioche[nblettre].nbRestant==0) //Tant qu'il ne reste pas des lettres dans la lettre choisie
                {
                    nblettre=rand()%28; //Selection aleatoire d'une lettre
                }
                /*
                system("cls");
                printf("%d [%d] %c [%c] ",nblettre,boucle,chevaletJoueur[boucle],pioche[nblettre].lettre);
                Sleep(1000);*/
                chevaletJoueur[boucle]=pioche[nblettre].lettre; //assignation de la lettre au chevalet

                pioche[nblettre].nbRestant--; //retrait d'une lettre dans la pioche
            }
            boucle++;
        }
    }
}

int verifChevaletsJoueurs(t_joueur players[4]) //Cherche si un chevalet est vide
{
    int j=0;
    int resultat=1,mainvide=1;
    for(int i=0; i<4; i++)//Boucle de passage des joueurs
    {
        mainvide=1; //Initialisation la main vide comme vraie
        resultat+=i; //Retourne le resultat, egal à la personne sur laquelle on est
        j=0; //Variable de passage dans le chevalet
        while(j<7) //Tant que pas fin du chevalet
        {
            if(players[i].chevalet[j]!='0') //Si la case i du chevalet a une lettre
            {
                j=6; //Fin du parcour de la main
                mainvide=0; //La main n'est pas vide
            }
            j++; //Incrémentation du passage dans la main
        }
        if(mainvide==1) //Si la main est vide à la sortie de la boucle
        {
            i=4; //Fin aprcour des joueurs
        }
    }
    return resultat; // retourne le numéro du joueur avec la main vide, sinon retourne 0
}


int verifPiocheVide(t_lettre pioche[27]) //Verification si il reste des lettres dans la pioche
{
    int result=1,i=0; // Resultat renvoie vrai
    while(pioche[i].nbRestant!=0 && i<27) //Tant qu'il reste une lettre non vide
    {
        result=0; // Resultat faux
        i++;
    }
    return result;
}


