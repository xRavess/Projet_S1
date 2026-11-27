#ifndef YEAR_DATA_H
#define YEAR_DATA_H

#define NB_ANNEES 20

typedef struct Statistiques_Annee {
    int annee;
    int nb_accidents;
    int nb_indemnes;
    int nb_morts;
    int nb_blesses_graves;
    int nb_blesses_legers;
} Statistiques_Annee;

typedef struct Victime{
    int annee;
    int id_collision;
    int id_vehicule;
    int emplacement;
    int type_utilisateur;
    int gravite;
    int genre;
    int annee_naissance;
    int motif_trajet;
}Victime;

void initialiserAnnees(Statistiques_Annee, tab[NB_ANNEES]);

void compterGravite(Statistiques_Annee tab[NB_ANNEES], int annee, int gravite);

void afficheStatistiques(Statistiques_Annee, tab[NB_ANNEES], int annee);

void menuAnnee(Statistiques_Annee, tab[NB_ANNEES]);

#endif
