#include "header_proj.h"

void calculFacteur(int *factMot,int* factLettre,char casePlateau) //sous programme de calcul des facteurs multplicatif d'une case
{
    switch(casePlateau) //change la valeurs des facteurs selon la case
    {
    case 2:
        (*factMot)*=3; //Si case 2/§ Mot compte triple, facteur mot est multplie par 3
        break;
    case 4:
        (*factMot)*=2; //Si case 4/@ Mot compte double, facteur mot est multplie par 2
        break;
    case 5:
        (*factLettre)*=3; //Si case 5/% Lettre compte triple, facteur lettre est multplie par 2
        break;
    case 3:
        (*factLettre)*=2; //Si case 3/& Lettre compte double, facteur lettre est multplie par 2
        break;
    }
}

int valeur_lettre(char lettre) // sprg pour valeur de chaque lettre (y compris le joker)
{
    int valeur=0;

    //Conditions permettant d'assigné le valeur de chaque lettre dans la pioche
    if(lettre=='A' || lettre=='E' || lettre=='I' || lettre=='L' || lettre=='N' || lettre=='O'|| lettre=='R'||lettre=='S'||lettre=='T'||lettre=='U')
    {
        valeur=1;
    }
    else if(lettre=='D' || lettre=='G' || lettre=='M')
    {
        valeur=2;
    }
    else if(lettre=='B' || lettre=='C'||lettre=='P')
    {
        valeur=3;
    }
    else if(lettre=='F'||lettre=='H'||lettre=='V')
    {
        valeur=4;
    }
    else if(lettre=='J' || lettre=='Q')
    {
        valeur=8;
    }
    else if(lettre=='K'||lettre=='W'||lettre=='X'||lettre=='Y'||lettre=='Z')
    {
        valeur=10;
    }
    else if(lettre=='?')
    {
        valeur=0; //égal à O pt pour le joker
    }

    return valeur;
}
