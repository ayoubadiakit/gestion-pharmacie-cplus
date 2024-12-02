#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>

/* Liste de toutes les structures du projet */

typedef struct //Structure medicament
{
    int num_medicament;
    char nom_medicament[30];
    int qte_stocke; //Quantité a stocke
    int prix_unit;
}medicament;

typedef struct
{
    int jour;
    int mois;
    int annee;
}date;

/* ------------------------------------------------------------ */

/* Prototype des fonctions du projet */
/* FONCTION DE MENU */

void menu_general();
void menu_med();
void menu_stok();
void menu_vente();

/* ------------------------------------------------------------ */
/* FONCTION DE GESTION DE MEDICAMENT */

void saisie_med(); //Fonction d'enregistrement d'un medicament
void affiche_med();
void supprime_med();
/* ------------------------------------------------------------ */
/* FONCTION DE GESTION DU STOCKE */

void Augmente_stock();
void verification();

/* ------------------------------------------------------------ */
/* FONCTION DE GESTION DE LA VENTE */
void vente_med();
void historique_vente();

/* ------------------------------------------------------------ */
/* AUTRE FONCTION */
/* ------------------------------------------------------------ */

#endif // HEADER_H_INCLUDED
