#include "header_proj.h"

int verificationOrthographique(char motAChercher[16])
{
    int validation=0; //Le mot est initialement faux
    char motDico[16]; //Stockage d'un mot du dictionnaire
    FILE *dico=NULL; //Pointeur sur le dictionnaire
    dico=fopen("dico.txt","r");
    if(dico==NULL)
    {
        printf("les pb");
    }
    else
    {
        //Boucle de passage dans le dictionnaire tant que condition non verifie
        //A savoir, fin du fichier ou mot trouvé
        while(!feof(dico) && validation==0)
        {
            fscanf(dico,"%s",motDico); //Recuperation d'un nouveau mot du dictionnaire

            if(strcmp(motAChercher,motDico)==0)//Si le mot est trouve
            {
                validation=1; //Le mot est bien orthographié
            }
        }
    }
    fclose(dico);
    return validation;
}

int poserUnMot(t_joueur *player,char plato[15][15][2])
{
    t_mot data_mot; //Information sur le mot a placer
    char buffer[7]; //Buffer du chevalet du joueur
    strcpy(buffer,player->chevalet); //Copy du chevalet dans le buffer
    int tailleMot; //Taille mot sert a blindé la saisit
    int validation=1; //Sert a savoir si le mot est posé ou non à la fin du programme

    do
    {
        gotoligcol(LIGNESAISIT,COLONNESAISIT); //Place le curseur au niveau de l'affichage pour saisir
        printf("Saisir votre mot: \n");
        scanf("%s",data_mot.word); //Prends le mot du joueur
        tailleMot=strlen(data_mot.word); //Recuperation de la taille du mot
    }
    while(tailleMot>15); //tant que le mot n'est pas a la bonne taille
    conversionMotMaj(data_mot.word);
    /*
        printf("saisir la colonne de la premiere lettre:\n");
        scanf("%d",&(data_mot.posColonne));

        printf("saisir la ligne de la premiere lettre:\n");
        scanf("%d",&(data_mot.posLigne));
    */
    if(verificationOrthographique(data_mot.word)==1)//Si le mot est bien orthographié
    {
        choixDirection(&data_mot); //On choisit la direction du mot (verticale horizontale)
        if(verifPlacementMot(data_mot,plato,player->chevalet)==1) //si le mot peut etre placé (assez de lettre et terrain ok)
        {
            placementMotPlateau(data_mot,plato,player);//Si toutes les conditions sont verifie, on place le mot
        }
        else
        {
            validation=0; //Sinon le mot est mal placé et n'a pas été placé
        }
    }
    else
    {
        validation=0;   //Sinon le mot mal orthographié et n'a pas été placé
    }
    return validation; //Renoie si le mot est posé ou non
}


void choixDirection(t_mot* data_mot)
{
    char touche;
    char Direction='V';
    gotoligcol(LIGNEPLATEAU*2,5);
    printf("Veuillez choisir une direction : [FLECHE DROITE][FLECHE GAUCHE]");
    gotoligcol(LIGNEPLATEAU*2+2,5);
    printf(" Verticale   Horizontale\n");
    while(touche!=ENTER)
    {
        if (kbhit())
        {
            touche=getch();

            switch(touche)

            {
            case FLGAUCHE :
                Direction='V';

                gotoligcol(LIGNEPLATEAU*2+2,5);
                printf(">");
                gotoligcol(LIGNEPLATEAU*2+2,15);
                printf("<");
                gotoligcol(LIGNEPLATEAU*2+2,17);
                printf(" ");
                gotoligcol(LIGNEPLATEAU*2+2,28);
                printf(" ");
                break;

            case FLDROITE :
                Direction='H';

                gotoligcol(LIGNEPLATEAU*2+2,5);
                printf(" ");
                gotoligcol(LIGNEPLATEAU*2+2,15);
                printf(" ");
                gotoligcol(LIGNEPLATEAU*2+2,17);
                printf(">");
                gotoligcol(LIGNEPLATEAU*2+2,28);
                printf("<");
                break;
            }

        }
    }
    data_mot->direction=Direction;
}


//Sous programme plaçant un mot et attribuant son score au joueur
void placementMotPlateau(t_mot data_mot,char plato[15][15][2],t_joueur *player)
{
    int taillemot=strlen(data_mot.word);//Variabale prenant le taille du mot a ecrire sur le plateau
    int score=0; //Stockage du score total du mot
    int facteurMultiMot=1; //Stockage du facteur multiplicatif total du score du mot selon son placement
    int facteurMultiLettre=1; // //Stockage du facteur multiplicatif total d'une lettre selon son placement

    switch(data_mot.direction) //Switch prenant un algorithme différent selon la direction du mot
    {
    case 'V': //Si la direction du mot est verticale
        for(int i=0; i<taillemot; i++) //Boucle de passage des lettres sont bien presente
        {
            //Si on place une nouvelle lettre
            if(data_mot.word[i]!=plato[data_mot.posLigne+i][data_mot.posColonne][1]) //Si la lettre n'est pas présent sur le plateau de jeu
            {
                facteurMultiLettre=1; //Reinitialise pour chaque lettre le facteur
                //Calcul du facteur multpiplicatif de la case
                calculFacteur(&facteurMultiMot,&facteurMultiLettre,plato[data_mot.posLigne+i][data_mot.posColonne][0]);
                for(int j=0; j<7; j++) //Parcours de la main du joueur
                {
                    if(data_mot.word[i]==player->chevalet[i] || player->chevalet[i]=='?') //Si la lettre est présente dans la main du joueur ou un joker
                    {
                        //assigne le score de la lettre au score total
                        score+=valeur_lettre(player->chevalet[i])*facteurMultiLettre;
                        player->chevalet[i]='0'; //la lettre part de la main du joueur

                        j=7; //fin de la boucle de la main
                    }
                }
            }
        }
        break; //fin case

    case 'H': //Si la direction du mot est horizontal
        for(int i=0; i<taillemot; i++) //Boucle de passage des lettres sont bien presente
        {
            //Si on place une nouvelle lettre
            if(data_mot.word[i]!=plato[data_mot.posLigne][data_mot.posColonne+i][1]) //Si la lettre n'est pas présent sur le plateau de jeu
            {
                facteurMultiLettre=1; //Reinitialise pour chaque lettre le facteur
                //Calcul du facteur multpiplicatif de la case
                calculFacteur(&facteurMultiMot,&facteurMultiLettre,plato[data_mot.posLigne+i][data_mot.posColonne][0]);
                for(int j=0; j<7; j++) //Parcours de la main du joueur
                {
                    if(data_mot.word[i]==player->chevalet[i] || player->chevalet[i]=='?') //Si la lettre est présente dans la main du joueur ou un joker
                    {
                        //assigne le score de la lettre au score total
                        score+=valeur_lettre(player->chevalet[i])*facteurMultiLettre;
                        player->chevalet[i]='0'; //la lettre part de la main du joueur

                        j=7; //fin de la boucle de la main
                    }
                }
            }
        }
        break;
    }

    score*=facteurMultiMot; //Ajout du facteur multiplicatif du mot au score
    player->score+=score;  //Ajout du score au joueur
}

//Ssprgm verifiant le placement du mot dans le plateau de jeu
int verifPlacementMot(t_mot data_mot,char plato[15][15][2],char buffer[7])
{
    int result=1; //Resultat renvoyer: initialisé comme vrai (mot peut etre place)
    int taillemot=strlen(data_mot.word);//Varibale prenant le taille du mot a ecrire sur le plateau

    switch(data_mot.direction) //Switch prenant un algortihme différent selon la direction du mot
    {
    case 'V': //Si la direction du mot est verticale
        if(taillemot+data_mot.posLigne<=15 ) //Si le mot ne depasse pas la taille du plateau en verticale
        {
            for(int i=0; i<taillemot; i++) //Boucle de passage verifiant les lettres sont bien presente
            {
                if(data_mot.word[i]!=plato[data_mot.posLigne+i][data_mot.posColonne][1]) //Si la lettre n'est pas présent sur la case du plateau de jeu
                {
                    if(plato[data_mot.posLigne+i][data_mot.posColonne][1]=='0') //si la case est vide
                    {
                        for(int j=0; j<7; j++) //Parcours de la main du joueur
                        {
                            if(data_mot.word[i]==buffer[i] || buffer[i]=='?') //Si la lettre est présente dans la main du joueur ou un joker
                            {
                                buffer[i]='0'; //la lettre part de la main du joueur
                                j=7; //fin de la boucle de la main
                            }
                            else //Sinon, Si condition jamais verifié jusqu'au dernier caractere de la boucle
                            {
                                result=0; // Le mot ne peut pas etre place
                                i=taillemot; //Fin parcours du mot
                            }
                        }
                    }
                    else //Si la case est différente de la lettre et n'est pas vide
                    {
                        result=0; // Le mot ne peut pas etre place
                        i=taillemot; //Fin parcours du mot
                    }

                }
            }
        }
        else //Si le mot depasse la taille du tableau
        {
            result=0; // Le mot ne peut pas etre place
        }
        break; //fin case

    case 'H': //Si la direction du mot est horizontal
        if(taillemot+data_mot.posColonne<=15 ) //Si le mot ne depasse pas la taille du plateau en horizontale
        {
            for(int i=0; i<taillemot; i++) //Boucle de passage verifiant les lettres sont bien presente
            {
                if(data_mot.word[i]!=plato[data_mot.posLigne][data_mot.posColonne+i][1]) //Si la lettre n'est pas présent sur la case du plateau de jeu
                {
                    if(plato[data_mot.posLigne][data_mot.posColonne+i][1]=='0') //si la case est vide
                    {
                        for(int j=0; j<7; j++) //Parcours de la main du joueur
                        {
                            if(data_mot.word[i]==buffer[i] || buffer[i]=='?') //Si la lettre est présente dans la main du joueur ou un joker
                            {
                                buffer[i]='0'; //la lettre part de la main du joueur
                                j=7; //fin de la boucle de la main
                            }
                            else //Sinon, Si condition jamais verifié jusqu'au dernier caractere de la boucle
                            {
                                result=0; // Le mot ne peut pas etre place
                                i=taillemot; //Fin parcours du mot
                            }
                        }
                    }
                    else //Si la case est différente de la lettre et n'est pas vide
                    {
                        result=0; // Le mot ne peut pas etre place
                        i=taillemot; //Fin parcours du mot
                    }
                }
            }
        }
        else //Si le mot depasse la taille du tableau
        {
            result=0; // Le mot ne peut pas etre place
        }
        break;
    }
    return result; //retourne la verification vrai ou faux
}
