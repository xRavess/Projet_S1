#include <stdio.h>
#include <stdlib.h>
#include "year_data.h"


void initialiserAnnees(Statistiques_Annee tab[NB_ANNEES]) {
    for (int i = 0; i < NB_ANNEES; i++) {
        tab[i].annee = 2005 + i;
        tab[i].nb_accidents = 0;
        tab[i].nb_indemnes = 0;
        tab[i].nb_morts = 0;
        tab[i].nb_blesses_graves = 0;
        tab[i].nb_blesses_legers = 0;
    }
}


void compterGravite(Statistiques_Annee tab[NB_ANNEES], int annee, int gravite) {
    int i = annee - 2005;

    if (i < 0 || i >= NB_ANNEES) {
        printf("Erreur : année invalide\n");
        exit(1);
    }

    if (gravite == 1) {
        tab[i].nb_indemnes++;
    } else if (gravite == 2) {
        tab[i].nb_morts++;
    } else if (gravite == 3) {
        tab[i].nb_blesses_graves++;
    } else if (gravite == 4) {
        tab[i].nb_blesses_legers++;
    } else {
        printf("Erreur : gravité invalide\n");
        exit(2);
    }
}

void afficherStatistiques(int annee, tab[NB_ANNEES] ){
    int i = annee - 2005;

    if (i < 0 || i >= NB_ANNEES) {
        printf("Erreur : année invalide\n");
        return;
    }

    printf("Nombre d'accidents : %d\n", tab[i].nb_accidents);
    printf("Nombre d'accidents : %d\n", tab[i].nb_indemnes);
    printf("Nombre d'accidents : %d\n", tab[i].nb_morts);
    printf("Nombre d'accidents : %d\n", tab[i].nb_blesses_graves);
    printf("Nombre d'accidents : %d\n", tab[i].nb_blesses_legers);

}

void menuAnnee(Statistiques_Annee tab[NB_ANNEES]) {
    int annee;

    do {
        printf("Saisir une année entre 2005 et 2024\n");
        printf("Saisir 0 pour quitter\n");

        if (scanf("%d", &annee) != 1) {
            printf("Erreur de saisie\n");
            return;
        }

        if (annee >= 2005 && annee <= 2024) {
            afficherStatistiques(annee, tab);
        }
        else if (annee != 0) {
            printf("Année invalide\n");
        }

    } while (annee != 0);
}
