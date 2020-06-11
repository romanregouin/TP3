#ifndef _GRAPHE_H_
#define _GRAPHE_H_
typedef struct a *parc_t;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s {
  int label;                 // label du sommet
  parc_t liste_arcs;         // arcs sortants du sommet
  struct s *sommet_suivant;  // sommet suivant dans le graphe
  int couleur;               // couleur du sommet
  int deja_parcouru;
  int etiq;
  int traite;
} sommet_t, *psommet_t;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une
  distance
*/

typedef struct a {
  int poids;              // poids de l arc
  psommet_t dest;         // pointeur sommet destinataire
  struct a *arc_suivant;  // arc suivant
  int deja_parcouru;

} arc_t, *parc_t;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/

typedef psommet_t pgraphe_t;

typedef struct chemin {
  int nb;
  psommet_t start;
  parc_t arcs;
} chemin_t, *pchemin_t;

psommet_t chercher_sommet(pgraphe_t g, int label);

void ajouter_arc(psommet_t o, psommet_t d, int distance);

int nombre_arcs(pgraphe_t g);

int nombre_sommets(pgraphe_t g);

void lire_graphe(char *file_name, pgraphe_t *g);

void ecrire_graphe(psommet_t p);

void ecrire_graphe_colorie(psommet_t p);

int colorier_graphe(pgraphe_t g);

void afficher_graphe_profondeur2(pgraphe_t g, int r);

void afficher_graphe_profondeur_rec(pgraphe_t g);

void afficher_graphe_profondeur(pgraphe_t g, int r);

void afficher_graphe_largeur(pgraphe_t g, int r);

void algo_dijkstra(pgraphe_t g, int r);

void afficher_graphe_profondeur_rec(pgraphe_t g);

void afficher_graphe_profondeur2(pgraphe_t g, int r);

void parcour_profondeur_V2(pgraphe_t g);

void afficher_graphe_profondeur_V2(pgraphe_t g, int r);

psommet_t traitement_dijkstra(psommet_t sommet);

void debugDijikstra(pgraphe_t g, int r);

int complet(pgraphe_t g);

pchemin_t creerChemin(pgraphe_t g, int* labels, int nb);

void printChemin(pchemin_t c);

int elementaire (pchemin_t c);

int degre_sortant_sommet(pgraphe_t g, psommet_t s);

int degre_entrant_sommet(pgraphe_t g, psommet_t s);

int degre_maximal_graphe(pgraphe_t g);

int degre_minimal_graphe(pgraphe_t g);

int independant(pgraphe_t g);

int complet(pgraphe_t g);

int regulier(pgraphe_t g);
#endif