#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"
using namespace std;

/* ------------------------------------------------------------ */

void Augmente_stock()
{
    system("color E0");
    FILE *ancien, *nouveau;
    medicament un_med;
    char nom_med[30];
    bool trouve_nom = false;
    int choix, nouvelle_qte, ch;
    ancien = fopen("INFO_MEDICAMENT.txt", "r");
    if(ancien==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    nouveau = fopen("tmp.txt","w");
    if(nouveau==NULL)
    {
        cout << "ERREUR DE CREATION !!";
        exit(1);
    }
    cout << "\n\t\tSAISIR LE NOM DU MEDICAMENT DONT LA QUANTITE DOIT ETRE AUGMENTER : ";
    cin >> nom_med;
    do
    {
        if(fread(&un_med,sizeof(medicament),1,ancien))
        {
            if(strcmp(nom_med,un_med.nom_medicament)==0)
            {
                trouve_nom = true;
                break;
            }
        }
    }
    while(!feof(ancien));
    fclose(ancien);
    if(trouve_nom ==true)
    {
        cout << "\n\t\tLA QUANTITE ACTUELLE DU MEDICAMENT EST : " << un_med.qte_stocke << endl;
    }
    else
    {
        cout << "\n\t\tMedicament introuvable dans la base de donnee \n\n";
        system("pause");
        cout << "\n\t\t0 : continuer a l'augmentation       1 : se retourner ... ";
        cin >> choix;
        if(choix==0)
        {
            system("cls");
            Augmente_stock();
        }
        else
        {
            system("cls");
            menu_stok();
        }
    }

    cout << "\n\t\tVEILLER SAISIR LA QUANTITE A AJOUTER : ";
    cin >> nouvelle_qte;
    while(nouvelle_qte<=0)
    {
        cout << "\n\n\t\tLa quantite a ajouter doit etre superieur a 0 ... ";
        cin >> nouvelle_qte;
    }

    cout << "\n\n\t\t\tVous voulez continue ou annuler l'operation ?\n\n";
    cout << "\t\t\t0 : Annuler      1 : Continuer ... ";
    cin >> ch;
    if(ch==0)
    {
        cout << "\n\t\tOperation annuler !  Redirection menu stock\n\n";
        system("pause");
        menu_stok();
    }
    ancien = fopen("INFO_MEDICAMENT.txt", "r");
    if(ancien==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    do
    {
        if(fread(&un_med,sizeof(medicament),1,ancien))
        {
            if(strcmp(nom_med,un_med.nom_medicament)==0)
            {
                un_med.qte_stocke+=nouvelle_qte;
                fwrite(&un_med,sizeof(medicament),1,nouveau);
            }
            else
            {
                fwrite(&un_med,sizeof(medicament),1,nouveau);
            }
        }

    }
    while(!feof(ancien));
    fclose(ancien);
    fclose(nouveau);

    nouveau = fopen("tmp.txt","r");
    if(nouveau==NULL)
    {
        cout << "ERREUR DE CREATION !!";
        exit(1);
    }

    ancien = fopen("INFO_MEDICAMENT.txt", "w");
    if(ancien==NULL)
    {
        cout << " ERREUR D'OUVERTURE !!";
        exit(1);
    }

    do
    {
        if(fread(&un_med,sizeof(medicament),1,nouveau))
        {

            fwrite(&un_med,sizeof(medicament),1,ancien);
        }
    }
    while(!feof(nouveau));
    fclose(ancien);
    fclose(nouveau);
    remove("tmp.txt");

    cout << "\n\t\tOPERATION REUSSIE\n\n";
    system("pause");
    cout << "\n\t\t0 : continuer a l'augmentation       1 : se retourner ... ";
    cin >> choix;
    if(choix==0)
    {
        system("cls");
        Augmente_stock();
    }
    else
    {
        system("cls");
        menu_stok();
    }

}

/* ------------------------------------------------------------ */

void verification()
{
    system("color E0");
    int choix;
    medicament m;
    FILE *fic = fopen("INFO_MEDICAMENT.txt", "r");
    if(fic==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    cout << "           |---------------------------------------------------------------|\n";
    cout << "           |             LISTE DES MEDICAMENTS DANS LE STOCK               |\n";
    cout << "           |---------------------------------------------------------------|\n";
    cout << "               NUMERO                   NOM                   QUANTITE          \n\n";


    do
    {
        if(fread(&m,sizeof(medicament),1,fic))
        {
            printf("%18d", m.num_medicament);
            printf("%27s", m.nom_medicament);
            printf("%20d", m.qte_stocke);
            cout << "\n\n";

        }
    }
    while(!feof(fic));
    system("pause");
    system("cls");
    menu_stok();

}

/* ------------------------------------------------------------ */
