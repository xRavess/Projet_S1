#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define max(a,b) ((a)>(b) ? (a):(b))
#define min(a,b) ((a)<(b) ? (a):(b))

typedef struct victime{
    uint8_t age;
    uint8_t type;
    uint8_t genre;
    uint8_t gravite;
    struct victime * suivant;
} Victime;

typedef struct vehicule{
    char id[4];
    uint8_t trajet;
    Victime *victimes;
    struct vehicule * suivant;
} Vehicule;

typedef struct arbre{
	uint64_t cle;        //année * 100000000 + collision_id
	struct arbre * fg;
	struct arbre * fd;
    Vehicule *vehicules;
	uint8_t eq;
}Arbre;

/*On utilise uint8_t et uint64_t pour une meilleur gestion de l'espace.
Aussi pour etre sur que la taille souhaite soit pris en compte sur tout les ordinateurs, meme windows en 32bit.*/


Victime * creerVictime(uint8_t age, uint8_t type, uint8_t genre, uint8_t gravite){
    Victime *v = malloc(sizeof(Victime));
    if(v==NULL){
        printf("Erreur de segmentation");
        exit(1);
    }

    v->age = age;
    v->type = type;
    v->genre = genre;
    v-> gravite = gravite;
    v->suivant = NULL;

    return v;
}

Vehicule * creerVehicule(const char *id, uint8_t trajet){
    Vehicule *v = malloc(sizeof(Vehicule));
    if(v==NULL){
        printf("Erreur de segmentation");
        exit(1);
    }

    strncpy(v->id, id, 3);
    v->id[3] = '\0';
    v->trajet = trajet;
    v->victimes = NULL;
    v->suivant = NULL;
    return v;
}

Arbre * creerAVL(uint64_t cle){
    Arbre * nouveau = malloc(sizeof(Arbre));
    if(nouveau == NULL){
        printf("Erreur de segmentation");
        exit(1);
    }

    nouveau->cle = cle;
    nouveau->fg = NULL;
    nouveau->fd = NULL;
    nouveau->vehicules = NULL;
    nouveau->eq = 0;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage : %s fichier.csv\n", argv[0]);
        return 1;
    }
    const char *chemin = argv[1];

    FILE *ficher = fopen(chemin, "r");
    if(ficher == NULL){
        fprintf(stderr, "Erreur : impossible d'ouvrir %s\n", chemin);
        exit(1);
    }

    char ligne[256];
    fgets(ligne, sizeof ligne, ficher);      // en-tête
    while(fgets(ligne, sizeof ligne, ficher) != NULL){
        printf("%s", ligne);
    }

    fclose(ficher);
    return 0;
}