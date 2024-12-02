#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "fonctions_menu.cpp"
using namespace std;

/* ------------------------------------------------------------ */

void saisie_med()
{
    system("color E0");
    medicament un_med;
    char nom[30];
    bool trouve_num = false, trouve_nom = false; //Var booleenne qui verifiera dans le fichier si le num et le nom saisie n'existe pas
    int num, choix, ch;
    FILE *fic = fopen("INFO_MEDICAMENT.txt", "r");
    if(fic==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    cout << "\n\t\tNUMERO DU MEDICAMENT : ";
    cin >> num;
    while(!feof(fic))
    {
        if(fread(&un_med,sizeof(medicament),1,fic)) //Si le pointeur de fichier arrive a lire les medicaments un par un
        {
            if(num == un_med.num_medicament) // Si le numero saisi est egal au meme numero dans le fichier
                trouve_num = true;
        }
    }
    fclose(fic);

    if(trouve_num) //if(touve_num == true)
    {
        cout << "\a\n\t\tUn medicament est deja enregistrer sur ce numero !!\n\n";
        system("pause");
    }
    else
    {
        fic = fopen("INFO_MEDICAMENT.txt", "r");
        cout << "\n\t\tNOM DU MEDICAMENT : ";
        cin >> nom;
        while(!feof(fic))
        {
            if(fread(&un_med,sizeof(medicament),1,fic))
            {
                if(strcmp(nom,un_med.nom_medicament)==0) //Si le nom saisi est egal au meme nom dans le fichier
                    trouve_nom = true;
            }
        }
        fclose(fic);
        if(trouve_nom) //if(touve_nom == true)
        {
            cout << "\a\n\t\tUn medicament est deja sur ce nom\n\n";
            system("pause");
            cout << "\n\t\t0 : continuer a enregistre       1 : se retourner ... ";
            cin >> choix;
            if(choix==0)
            {
                system("cls");
                saisie_med();
            }
            else
            {
                system("cls");
                menu_med();
            }

        }
        fic = fopen("INFO_MEDICAMENT.txt","a+");
        un_med.num_medicament = num;
        strcpy(un_med.nom_medicament, nom);
        cout << "\n\t\tQUANTITE A STOCKE : ";
        cin >> un_med.qte_stocke;
        while(un_med.qte_stocke<=0) //Controle de la saisie pour une quantite negative ou egale a 0
        {
            cout << "\n\a\t\tLa quantite doit etre superieur a 0 : ";
            cin >> un_med.qte_stocke;
        }
        cout << "\n\t\tPRIX UNITAIRE : ";
        cin >> un_med.prix_unit;
        while(un_med.prix_unit<=0) //Controle de la saisie pour un prix negative ou egale a 0
        {
            cout << "\n\a\t\tLe prix doit etre superieur a 0 : ";
            cin >> un_med.prix_unit;
        }
        cout << "\n\t\t\tVous voulez vraiment enregistre le medicament ?\n";
        cout << "\n\t\t\t1 : OUI ou 0 : NON ... ";
        cin >> ch;
        if(ch==0)
        {
            cout << "\n\t\tCommande annuler !   Redirection : menu medicament ...\n\n";
            system("pause");
            system("cls");
            menu_med();
        }
        else
        {
            fwrite(&un_med,sizeof(medicament),1,fic); //Ecriture du medicament enregistre dans le fichier (base de donnee)
            fclose(fic);
            cout << "\n\t\tMedicament enregistre avec succes\n\n";
            system("pause");
            cout << "\n";
        }
    }
    cout << "\n\t\t0 : continuer a enregistre       1 : se retourner ... ";
    cin >> choix;
    if(choix==0)
    {
        system("cls");
        saisie_med();
    }
    else
    {
        system("cls");
        menu_med();
    }

}

/* ------------------------------------------------------------ */

void affiche_med()
{
    system("color E0");
    bool trouve_med = false;
    char nomProduit[30];
    medicament m;
    int choix;
    FILE *f = fopen("INFO_MEDICAMENT.txt", "r");
    if(f == NULL)
    {
        cout << " ERREUR D'OUVERTURE !";
        exit(1);
    }
    cout << "\n\t\tSAISIR LE NOM DU MEDICAMENT A AFFICHER : ";
    cin >> nomProduit;
    do
    {
        if(fread(&m,sizeof(medicament),1,f))
        {
            if(strcmp(nomProduit, m.nom_medicament)==0)
            {
                trouve_med = true;
                system("cls");
                cout << "\n\t\t*********** LES INFORMATIONS DU MEDICAMENT **********\n\n";
                cout << "\n\t\t\t\tNUMERO MEDICAMENT : " << m.num_medicament << "\n\n";
                cout << "\n\t\t\t\tNOM DU MEDICAMENT : " << m.nom_medicament << "\n\n";
                cout << "\n\t\t\t\tPRIX UNITAIRE : " << m.prix_unit << " GNF\n\n";
                cout << "\n\t\t\t\tQUANTITE STOCKE : " << m.qte_stocke << "\n\n";
            }
        }
    }
    while(!feof(f));
    fclose(f);

    if(trouve_med == false)
    {
        cout << "\a\n\t\tMedicament introuvable dans la base de donnee !!\n\n";
        system("pause");
    }
    cout << "\n\t\t0 : continuer a afficher       1 : se retourner ... ";
    cin >> choix;
    if(choix==0)
    {
        system("cls");
        affiche_med();
    }
    else
    {
        system("cls");
        menu_med();
    }

}

/* ------------------------------------------------------------ */

void supprime_med()
{
    system("color E0");
    FILE *ancien, *nouveau;
    medicament un_med;
    char nom_med[30];
    bool trouve_nom = false;
    int choix, ch;
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
    cout << "\n\t\tSAISIR LE NOM DU MEDICAMENT A SUPPRIMER : ";
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
    if(trouve_nom==false)
    {
        cout << "\a\n\t\tMedicament introuvable dans la base de donnee\n\n";
        system("pause");
        cout << "\n\t\t0 : continuer a supprimer       1 : se retourner ... ";
        cin >> choix;
        if(choix==0)
        {
            system("cls");
            supprime_med();
        }
        else
        {
            system("cls");
            menu_med();
        }
    }

    cout << "\n\t\t\tEtes vous sur de vouloir supprimer le medicament '" << un_med.nom_medicament << "' ?\n\n" ;
    cout << "\n\t\t\t1 : OUI ou 0 : NON ... ";
    cin >> ch;
    if(ch==0)
    {
        cout << "\n\t\tSuppression annuler !   Redirection : menu medicament ...\n\n";
        system("pause");
        system("cls");
        menu_med();
    }
    ancien = fopen("INFO_MEDICAMENT.txt", "r");
    if(ancien==NULL)
    {
        cout << " ERREUR D'OUVERTURE !!";
        exit(1);
    }

    do
    {
        if(fread(&un_med,sizeof(medicament),1,ancien))
        {
            if(strcmp(nom_med,un_med.nom_medicament)!=0)
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
    cout << "\n\t\tMedicament supprimer avec succes\n\n";
    system("pause");

    cout << "\n\t\t0 : continuer a supprimer       1 : se retourner ... ";
    cin >> choix;
    if(choix==0)
    {
        system("cls");
        supprime_med();
    }
    else
    {
        system("cls");
        menu_med();
    }
}

/* ------------------------------------------------------------ */
