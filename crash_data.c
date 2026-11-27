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
    int8_t trajet;
    Victime *victimes;
    struct vehicule * suivant;
} Vehicule;

typedef struct arbre{
	uint64_t cle;        //année * 100000000 + collision_id
	struct arbre * fg;
	struct arbre * fd;
    Vehicule *vehicules;
	int8_t eq;
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

Vehicule * creerVehicule(const char *id, int8_t trajet){
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

    return nouveau;
}

Arbre * rotationGauche(Arbre *a){
    Arbre *pivot = a->fd;
    int eq_a = a->eq, eq_p = pivot->eq;

    a->fd = pivot->fg;
    pivot->fg = a;
    a->eq = eq_a - max(eq_p, 0) - 1;
    pivot->eq = min(min(eq_a - 2, eq_a + eq_p - 2), eq_p - 1);
    return pivot;
}

Arbre * rotationDroite(Arbre *a){
    Arbre *pivot = a->fg;
    int eq_a = a->eq, eq_p = pivot->eq;

    a->fg = pivot->fd;
    pivot->fd = a;
    a->eq = eq_a - min(eq_p, 0) + 1;
    pivot->eq = max(max(eq_a + 2, eq_a + eq_p + 2), eq_p + 1);
    return pivot;
}

Arbre * doubleRotationGauche(Arbre *a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

Arbre * doubleRotationDroite(Arbre *a){
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

Arbre * equilibrerAVL(Arbre * a){
    if(a->eq >= 2){
        if(a->fd->eq >= 0) return rotationGauche(a);
        return doubleRotationGauche(a);
    }
    if(a->eq <= -2){
        if(a->fg->eq <= 0) return rotationDroite(a);
        return doubleRotationDroite(a);
    }
    return a;
}


Arbre * insererAVL(Arbre * a, uint64_t cle, int *h, Arbre **noeud){
    if(a == NULL){
        *h = 1;
        a = creerAVL(cle);
        *noeud = a;
        return a;
    }
    if(cle == a->cle){          // accident déjà présent
        *h = 0;
        *noeud = a;
        return a;
    }
    if(cle < a->cle){
        a->fg = insererAVL(a->fg, cle, h, noeud);
        *h = -*h;               // pousser à gauche diminue l'équilibre
    } else {
        a->fd = insererAVL(a->fd, cle, h, noeud);
    }
    if(*h != 0){
        a->eq += *h;
        a = equilibrerAVL(a);
        *h = (a->eq == 0) ? 0 : 1;
    }
    return a;
}


void afficherInfixe(Arbre * a){
    if(a == NULL) return;
    afficherInfixe(a->fg);
    printf("%llu (eq=%d)\n", (unsigned long long)a->cle, a->eq);
    afficherInfixe(a->fd);
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

    Arbre *racine = NULL, *noeud;
    int h;
    uint64_t test[] = {5, 3, 8, 1, 2, 9, 10, 7, 4, 6};
    for(int i = 0; i < 10; i++){
        h = 0;
        racine = insererAVL(racine, test[i], &h, &noeud);
    }
    afficherInfixe(racine);

    return 0;
}