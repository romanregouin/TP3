#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

int main(int argc, char** argv) {
  pgraphe_t g;
  int nc;

  if (argc != 3) {
    fprintf(stderr, "Syntaxe : %s [FICHIER] [LABEL_SOMMET]\n", argv[0]);
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
  
  nc = colorier_graphe(g);

  printf("nombre chromatique graphe = %d\n", nc);

  ecrire_graphe_colorie(g);

  printf("\nParcours profondeur LIAM Version : \n");

  afficher_graphe_profondeur2(g, label);

  printf("\nParcours profondeur ROMAN Version : \n");

  afficher_graphe_profondeur_V2(g, label);

  printf("\nParcours largeur :\n");

  afficher_graphe_largeur(g,label);

  printf("\nDIJIKSTRA : \n");

  algo_dijkstra(g, label);

  if (complet(g)) printf("\nLe graphe est Complet ! \n");

  /*int* labels = malloc(4 * sizeof(int));
  labels[0] = 0;
  labels[1] = 1;
  labels[2] = 2;
  labels[3] = 0;

  pchemin_t chemin = creerChemin(g, labels, 4);

  printChemin(chemin);
  printf("Test Roman \n\n");
  if (elementaire(chemin)) {
    printf("Le chemin est élémentaire\n");
  }
  if (simple(chemin)) {
    printf("Le chemin est simple\n");
  }
  labels[0] = 1;
  labels[1] = 2;
  labels[2] = 4;
  labels[3] = 1;
  labels[4] = 3;
  labels[5] = 4;
  labels[6] = 1;

  pchemin_t chemin = creerChemin(g, labels, 6);
  printf("Test Liam \n\n");
  printChemin(chemin);
  if (elementaire(chemin)) {
    printf("Le chemin est élémentaire\n");
  }
  if (simple(chemin)) {
    printf("Le chemin est simple\n");
  }

  printf("La distance entre %d et %d est de %d \n", labels[0], labels[1],
         distance(g, labels[0], labels[1]));

  if (hamiltonien(g,chemin)) {
    printf("Le chemin est hamiltonien\n");
  }

  if(eulerien(g,chemin)){
    printf("Le chemin est eulerien\n");
  }*/

  printf("\nDegre entrant du sommet %d : %d \n", label,
         degre_entrant_sommet(g, chercher_sommet(g, label)));
  printf("\nDegre sortant du sommet %d : %d \n", label,
         degre_sortant_sommet(g, chercher_sommet(g, label)));
  printf("\nDegre maximal du graphe : %d \n", degre_maximal_graphe(g));
  printf("\nDegre minimal du graphe : %d \n\n", degre_minimal_graphe(g));
  printf("Exentricite du sommet %d : %d \n\n", label, excentricite(g,label));
  printf("Diametre du graphe : %d \n", diametre(g));

  if (regulier(g)) printf("\nLe graphe est Regulier !  \n");
  if (independant(g)) printf("\nLe graphe est Independant ! \n");
  if (graphe_eulerien(g)){
    printf("\nLe graphe est eulerien !\n");
  }
  return 0;
}