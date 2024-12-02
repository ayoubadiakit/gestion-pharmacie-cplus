#include <iostream>
#include <stdlib.h>
#include "header.h"
using namespace std;

/* ------------------------------------------------------------ */

void menu_general()
{
    int choix;
    system("color E0");

    do
    {
        cout << "\n\n";
        cout << "\t\t\t\t _______________________________________\n";
        cout << "\t\t\t\t|\t\tMENU GENERAL\t\t| \n";
        cout << "\t\t\t\t|_______________________________________|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|\t1 : GESTION DE MEDICAMENTS\t|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|\t2 : GESTION DU STOCKE\t\t|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|\t3 : GESTION DE LA VENTE\t\t|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|                       \t\t|\n";
        cout << "\t\t\t\t|\t4 : QUITTER\t\t\t|\n";
        cout << "\t\t\t\t|_______________________________________|\n\n";
        cout << "\t\t\t\t\tQUE VOULEZ-VOUS FAIRE ?? ... ";

        cin >> choix;
        switch(choix)
        {
        case 1:
        {
            system("cls");
            menu_med();
            break;
        }
        case 2:
        {
            system("cls");
            menu_stok();
            break;
        }
        case 3:
        {
            system("cls");
            menu_vente();
            break;
        }
        case 4:
        {
            system("cls");
            system("color 30");
            cout << "\n MERCI A BIENTOT !\n\n";
            system("pause");
            exit(0);
        }
        default:
        {
            system("cls");
            cout << "FAITE UN CHOIX SELON LE MENU !\n";
        }
        }
    }
    while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
}

/* ------------------------------------------------------------ */

void menu_med()
{
    int choix;
    system("color E0");
    do
    {
        cout << "\n\n";
        cout << "\t\t\t 1 : ENREGISTRER DE NOUVEAU MEDICAMENT\n\n\n";
        cout << "\t\t\t 2 : AFFICHER UN MEDICAMENT\n\n\n";
        cout << "\t\t\t 3 : SUPPRIMER UN MEDICAMENT\n\n\n";
        cout << "\t\t\t 4 : RETOUR AU MENU GENERAL\n\n";
        cout << "\t\t\t\t   FAITE UN CHOIX ... ";
        cin >> choix;
        switch(choix)
        {
        case 1:
        {
            system("cls");
            saisie_med();
            break;
        }
        case 2:
        {
            system("cls");
            affiche_med();
            break;
        }
        case 3:
        {
            system("cls");
            supprime_med();
            break;
        }
        case 4:
        {
            system("cls");
            menu_general();
            break;
        }
        default:
        {
            system("cls");
            cout << "\n\t\t\tFAITE UN CHOIX SELON LE MENU ";
        }
        }
    }
    while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
}

/* ------------------------------------------------------------ */

void menu_stok()
{
    int choix;
    system("color E0");
    do
    {
        cout << "\n\n";
        cout << "\t\t\t\t 1 : AUGMENTER LE STOCKE D'UN MEDICAMENT\n\n\n\n";
        cout << "\t\t\t\t 2 : VERIFIER LE STOCKE DISPONIBLE\n\n\n\n";
        cout << "\t\t\t\t 3 : RETOUR AU MENU GENERAL\n\n\n\n";
        cout << "\t\t\t\t\t   FAITE UN CHOIX ... ";
        cin >> choix;
        switch(choix)
        {
        case 1:
        {
            system("cls");
            Augmente_stock();
            break;
        }
        case 2:
        {
            system("cls");
            verification();
            break;
        }
        case 3:
        {
            system("cls");
            menu_general();
            break;
        }
        default:
        {
            system("cls");
            cout << "\n\t\t\tFAITE UN CHOIX SELON LE MENU ";
        }
        }
    }
    while(choix!=1 && choix!=2 && choix!=3);
}

/* ------------------------------------------------------------ */

void menu_vente()
{
    int choix;
    system("color E0");
    do
    {
        cout << "\n\n";
        cout << "\t\t\t\t 1 : VENDRE UN MEDICAMENT\n\n\n\n\n";
        cout << "\t\t\t\t 2 : HISTORIQUE DE LA VENTE\n\n\n\n\n";
        cout << "\t\t\t\t 3 : RETOUR AU MENU GENERAL\n\n\n";
        cout << "\t\t\t\t        FAITE UN CHOIX ... ";
        cin >> choix;
        switch(choix)
        {
        case 1:
        {
            system("cls");
            vente_med();
            break;
        }
        case 2:
        {
            system("cls");
            historique_vente();
            break;
        }
        case 3:
        {
            system("cls");
            menu_general();
            break;
        }
        default:
        {
            system("cls");
            cout << "\n\t\t\tFAITE UN CHOIX SELON LE MENU ";
        }
        }
    }while(choix!=1 && choix!=2 && choix!=3);
}





/* ------------------------------------------------------------ */
