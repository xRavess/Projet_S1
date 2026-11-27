#inlcude <stdio.h>
#include <stdlib.h>


// 1. Représente UNE personne (une ligne lue dans le CSV)
typedef struct {   
    int annee_incident;
    int annee_naissance;
    int role;   // 1: conducteur, 2: passager, 3: piéton
    int genre;  // 1: masculin, 2: féminin, etc.
} Victime;


typedef struct {    // 2. Représente les statistiques cumulées pour UN âge précis
    int age;
    int conducteur;
    int passager;
    int pieton;
    int masculin;
    int feminin;
    int autre_genre;
} StatsAge;


// 3. Le maillon de la liste chaînée
typedef struct NodeAge {
    StatsAge stats;          // Les stats de cet âge
    struct NodeAge* suivant; 
} NodeAge;


int calculerAge(Victime* v, int annee_incident){
    if (v == NULL){
        exit(1);
    }
    return (annee_incident - v->annee_naissance);
}


NodeAge* insererOuMettreAJourAge(NodeAge* tete, Victime* v, int annee_incident) {
    int age = calculerAge(v, annee_incident);
    
    // 2. TODO: Parcourir la liste pour voir si l'âge existe déjà
    NodeAge* temp = tete;
    while(temp != NULL){
        if (temp->stats.age == age){
            
            if (v->role == 1) {
            temp->stats.conducteur++;
            } else if (v->role == 2) {
            temp->stats.passager++;
            } else if (v->role == 3) {
            temp->stats.pieton++;
            }

            if (v->genre == 1) {
            temp->stats.masculin++;
            } else if (v->genre == 2) {
            temp->stats.feminin++;
            } else {
            temp->stats.autre_genre++;
            }
            
            return temp;
       }
        
        temp = temp->suiv;
    }
    

    //creation du nouveau noeud .
      NodeAge* nv = (NodeAge*)malloc(sizeof(NodeAge));
      if(nv == NULL){
       return NULL;
      }
    
      nv->stats.age = age;     
      nv->stats.conducteur = 0;
      nv->stats.passager = 0;
      nv->stats.pieton = 0;
      nv->stats.masculin = 0;
      nv->stats.feminin = 0;
      nv->stats.autre_genre = 0;

      if(v->role == 1){                 
          nv->stats.conducteur = 1;
      } else if(v->role == 2){
          nv->stats.passager = 1;
      } else if(v->role == 3){
          nv->stats.pieton = 1;
      }

      if(v->genre == 1){            
          nv->stats.masculin = 1;
      } else if(v->genre == 2){
          nv->stats.feminin = 1;
      } else {
          nv->stats.autre_genre = 1;
      }
    
      nv->suivant = NULL;


    //insertion du nouveau noeud
    //insertion au tout début
    if (tete == NULL || age < tete->stats.age) {
        nv->suivant = tete;
        return nv; // Le nouveau devient la tête
    }

    //insertion au milieu/fin
    NodeAge* courant = tete;
    while (courant->suivant != NULL && courant->suivant->stats.age < age) {
        courant = courant->suivant;
    }
    nv->suivant = courant->suivant;
    courant->suivant = nv;
    return tete;
}
    
    
 filtre fonction femme / fontion homme / fonction pieton....
     mais ca ne sera pas croisé?












