#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"
using namespace std;

/*void bienvenu()
{
    cout << nbr_medicament() << " medicament dans la base de donnee\n\n";
    system("pause");
    cout << "Affichage du menu general ...\n\n";
    system("pause");
    menu_general();
}*/

int nbr_medicament()
{
    medicament un_med;
    int compteur = 0;
    FILE *fic = fopen("INFO_MEDICAMENT.txt", "r");
    if(fic==NULL)
    {
        cout << "ERREUR D'OUVERTURE !!";
        exit(1);
    }
    do
    {
        if(fread(&un_med,sizeof(medicament),1,fic))
        {
            compteur++;
        }
    }while(!feof(fic));
    return compteur;
}
