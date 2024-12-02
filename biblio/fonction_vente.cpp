#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"
#include <time.h>
using namespace std;

void vente_med()
{
    system("color E0");
    FILE *ancien, *nouveau; //Pointeur de ficher pour le ficher 'INFO_MEDICAMENT' et 'tmp'
    medicament un_med;
    date d; // Variable de type struct medicament
    char nom_med[30];
    bool trouve_nom = false, qte_negatif = false;
    int choix, nouvelle_qte, prix_client, ch;
    float somme_paye = 0;
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

    cout << "\n\t\tSAISIR LE NOM DU MEDICAMENT A VENDRE : ";
    cin >> nom_med;
    do
    {
        if(fread(&un_med,sizeof(medicament),1,ancien)) //Si le pointeur de fichier arrive a lire les medicament un a un
        {
            if(strcmp(nom_med,un_med.nom_medicament)==0) // Si les deux noms correspond
            {
                trouve_nom = true;
                break;
            }
        }
    }
    while(!feof(ancien));
    fclose(ancien);
    if(trouve_nom==false)
    {
        cout << " \n\t\tMedicament introuvable dans la base de donnee\n\n";
        cout << "\n\t\t0 : continuer la vente       1 : se retourner ... ";
        cin >> choix;
        if(choix==0)
        {
            system("cls");
            vente_med();
        }
        else
        {
            system("cls");
            menu_vente();
        }
    }

    cout << "\n\t\tSAISIR LA QUANTITE A VENDRE (max " << un_med.qte_stocke << ") : ";
    cin >> nouvelle_qte;
    if(un_med.qte_stocke==0)
    {
        cout << "\n\t\tLe medicament est fini !\n\n";
        system("pause");
        cout << "\n\t\t0 : continuer la vente       1 : se retourner ... ";
        cin >> choix;
        if(choix==0)
        {
            system("cls");
            vente_med();
        }
        else
        {
            system("cls");
            menu_vente();
        }
    }

    while(nouvelle_qte > un_med.qte_stocke || nouvelle_qte<0)
    {
        cout << "\a\n\t\tErreur de saisie veiller reprendre ... ";
        cin >> nouvelle_qte;
    }
    cout << "\n\t\tSaisie de la date FORMAT(jour mois annee) : ";
    cin >> d.jour >> d.mois >> d.annee;
    somme_paye = un_med.prix_unit*nouvelle_qte;
    cout << "\n\t\tLa somme a paye est : " << somme_paye <<" GNF" << endl;
    cout << "\n\t\tSaisisser le prix du client : ";
    cin >> prix_client;
    while(prix_client < somme_paye)
    {
        cout << "\a\n\t\tPrix incorrecte ressaisissez le prix : ";
        cin >> prix_client;
    }

    cout << "\n\n\t\t\tVous voulez continue ou annuler l'operation ?\n\n";
    cout << "\t\t\t0 : Annuler      1 : Continuer ... ";
    cin >> ch;
    if(ch==0)
    {
        cout << "\n\t\tCommande annuler !   Redirection  menu vente ...\n\n";
        system("pause");
        system("cls");
        menu_vente();
    }

    ancien = fopen("INFO_MEDICAMENT.txt", "r");
    if(ancien==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    FILE *autre = fopen("INFO_VENTE.txt","a");
    if(autre==NULL)
    {
        cout << "ERREUR DE CREATION !!";
        exit(1);
    }

    do
    {
        if(fread(&un_med,sizeof(medicament),1,ancien))
        {
            if(strcmp(nom_med,un_med.nom_medicament)==0 && un_med.qte_stocke>=0) //si le nom saisi correspond au nom saisi et que la qte est >=0
            {
                un_med.qte_stocke-=nouvelle_qte; // Diminution de la quantite car il ya eu vente donc la quantite doit diminuer
                fwrite(&un_med,sizeof(medicament),1,nouveau); // Ecriture du medicament modifier dans un ficher temporaire 'tmp'
                un_med.qte_stocke = nouvelle_qte; // Modification de la quantite du medicament par la quantite saisie
                fwrite(&un_med,sizeof(medicament),1,autre); // Ecriture du medicament modifier dans le fichier 'VENTE'
                fwrite(&d,sizeof(date),2,autre);

            }
            else //Si les deux noms ne correspond pas sa veut dire que ce n'est pas le medicament a vendre
            {
                fwrite(&un_med,sizeof(medicament),1,nouveau); // Ecriture du medicament correspondant dans le fichier 'tmp'
            }
        }

    }
    while(!feof(ancien));
    fclose(ancien);
    fclose(nouveau);
    fclose(autre);

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

    cout << "\n\n\t\tOPERATION REUSSIE\n\n";
    system("pause");
    system("cls");
    /* ----------------------------------------------------------------------------------------- */
    time_t t; // Affichage de la date et de l'heure dans la console
    time(&t);
    char * time_str = ctime(&t);
    time_str[strlen(time_str)-1] = '\0';
    /*Manière d'affichée les info après une commande passée*/
    char linebreak2[73]="+-------------------------------+--------------------+----------------+\n";
    printf("\n\t\t%s",linebreak2);
    printf("\t\t|  Commande passe le : \t\t\t%d/%d/%d\t      \t      |\n",d.jour,d.mois,d.annee);
    printf("\t\t%s",linebreak2);
    printf("\t\t|Nom                            |Quantite            |Somme           |\n");
    printf("\t\t%s",linebreak2);
    printf("\t\t|%-31s|%-20d|%-12.0f GNF|\n",un_med.nom_medicament,nouvelle_qte,somme_paye);
    printf("\t\t%s",linebreak2);
    printf("\t\t|TOTAL DE LA COMMANDE %44.0f GNF|\n",somme_paye);
    printf("\n\t\t|PRIX DU CLIENT%51d GNF|\n",prix_client);
    printf("\n\t\t|MONNAIE RENDU%52.0f GNF|\n",prix_client-somme_paye);
    printf("\t\t%s",linebreak2);
    /* ----------------------------------------------------------------------------------------- */
    cout << "\n\n";
    system("pause");
    cout << "\n\t\t0 : continuer la vente       1 : se retourner ... ";
    cin >> choix;
    if(choix==0)
    {
        system("cls");
        vente_med();
    }
    else
    {
        system("cls");
        menu_vente();
    }

}

void historique_vente()
{
    system("color E0");
    medicament un_med;
    date d;
    int nouvelle_qte;
    bool trouve_med = false;
    FILE *fic = fopen("INFO_VENTE.txt", "r");
    if(fic==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    cout << " |---------------------------------------------------------------------------------------------------|\n";
    cout << " |                                    HISTORIQUE DE LA VENTE                                         |\n";
    cout << " |---------------------------------------------------------------------------------------------------|\n";
    cout << " |  Date de la vente        Numero            Nom              Quantite              Prix vendu      |\n";
    cout << " |---------------------------------------------------------------------------------------------------|\n";

    do
    {
        if(fread(&un_med,sizeof(medicament),1,fic))
        {
            trouve_med = true;
            if(fread(&d,sizeof(date),2,fic))
            {
                cout << "      " << d.jour << "/" << d.mois << "/" << d.annee;
            }
            cout << "\t\t     " << un_med.num_medicament << "\t\t     ";
            cout << un_med.nom_medicament << "\t\t";
            cout << un_med.qte_stocke << "\t\t     ";
            cout << un_med.prix_unit << " GNF";
            cout << "\n\n\n";
        }
    }
    while(!feof(fic));
    fclose(fic);
    cout << "\n\n";
    system("pause");
    system("cls");
    menu_vente();
}

