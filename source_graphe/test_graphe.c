#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

int main(int argc, char **argv) {
  pgraphe_t g;
  // int nc;

  if (argc != 3) {
    fprintf(stderr, "Syntaxe : ./%s [FICHIER] [LABEL_SOMMET]\n", argv[0]);
    exit(-1);
  }

  int label = atoi(argv[2]);

  /*
    la fonction lire_graphe alloue le graphe (matrice,...)
    et lit les donnees du fichier passe en parametre
  */

  lire_graphe(argv[1], &g);

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran


  printf("nombre de sommets du graphe %d nombre arcs %d \n",
  nombre_sommets(g), nombre_arcs(g)); fflush(stdout);
  */
  ecrire_graphe(g);
  /*
  nc = colorier_graphe(g);

  printf("nombre chromatique graphe = %d\n", nc);

  ecrire_graphe_colorie(g);

  printf("LIAM Version : \n");

  afficher_graphe_profondeur2(g, label);

  printf("ROMAN Version : \n");

  afficher_graphe_profondeur_V2(g, label);*/

  printf("DIJIKSTRA : \n");

  algo_dijkstra(g, label);

  if (complet(g)) printf("Le graphe est Complet ! \n");

<<<<<<< HEAD
  int* labels = malloc(4*sizeof(int));
  labels[0] = 0; labels [1] = 2; labels[2] = 8; labels[3] = 5;

  pchemin_t chemin = creerChemin(g,labels,4);
  int test = elementaire(chemin);
=======
  printf("Degre entrant du sommet %d : %d \n", label,
         degre_entrant_sommet(g, chercher_sommet(g, label)));
  printf("Degre sortant du sommet %d : %d \n", label,
         degre_sortant_sommet(g, chercher_sommet(g, label)));
  printf("Degre maximal du graphe : %d \n", degre_maximal_graphe(g));
  printf("Degre minimal du graphe : %d \n", degre_minimal_graphe(g));

  if (regulier(g)) printf("Le graphe est Regulier !  \n");
  if (independant(g)) printf("Le graphe est Independant ! \n");
>>>>>>> dd50827fb0299953886ed942846e03985eacbbd8
}
