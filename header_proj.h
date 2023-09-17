#ifndef HEADER_PROJ_H_INCLUDED
#define HEADER_PROJ_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define FLDROITE 77
#define FLGAUCHE 75
#define FLBAS 80
#define FLHAUT 72
#define ENTER 13
#define ESC 27
#define LIGNEPLATEAU 3
#define COLONNEPLATEAU 8
#define LIGNEMENU 10
#define COLONNEMENU 110
#define LIGNESAISIT 39
#define COLONNESAISIT 12

typedef struct lettre
{
    char lettre;
    int nbRestant;

} t_lettre;

typedef struct joueur
{
    char name[15];
    int score;
    char chevalet[7];
} t_joueur;

typedef struct mot
{
    char word[16];
    char direction;
    int posLigne;
    int posColonne;
} t_mot;


void initPioche(t_lettre pioche[27]);
void affPioche(t_lettre pioche[27]);
int verifPiocheVide(t_lettre pioche[27]);


void initInfoJoueur(t_joueur *data);
void affichageInfoJoueur(t_joueur database);
void affichageTableauJoueur(t_joueur player[4],int nbJoueur);

void initialisationPlateaudeJeu(char plato[15][15][2]);
void sauvegardePartie(char Plato[15][15][2],t_joueur player[4],int *nbJoueurs,t_lettre pioche[27]);
void chargementPartie(char plato[15][15][2],t_joueur player[4],int *nbJoueurs,t_lettre pioche[27]);
int demande_sauvegarde();

void affichagePlateauDeJeu(char plato[15][15][2]);
void Color(int couleurDuTexte,int couleurDeFond);
void effacerSaisitJoueur();
void gotoligcol(int lig, int col);
void curseurOFF();
void aide();
void balise1();
void balise2();

void partie(int choiceMenu);
void initialisation_Nouvelle_Partie(t_joueur player[4],t_lettre pioche[27],char plato[15][15][2],int *nbJoueurs);

int verifChevaletsJoueurs(t_joueur players[4]);
int valeur_lettre(char lettre);
void calculFacteur(int *factMot,int* factLettre,char casePlateau);
void piocherLettre(t_lettre pioche[27],char chevaletJoueur[7]);
void retirerLettre(char chevalet[7],t_lettre pioche[27]);

void position(t_mot *data_mot);


int verificationOrthographique(char motAChercher[16]);
int verifPlacementMot(t_mot data_mot,char plato[15][15][2],char chevalet[7]);
void placementMotPlateau(t_mot data_mot,char plato[15][15][2],t_joueur *player);
int poserUnMot(t_joueur *player,char plato[15][15][2]);
void choixDirection(t_mot* data_mot);
void conversionMotMaj(char cara[16]);
#endif // HEADER_PROJ_H_INCLUDED
