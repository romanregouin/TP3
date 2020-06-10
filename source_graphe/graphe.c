/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include "graphe.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "pile.h"

psommet_t chercher_sommet(pgraphe_t g, int label) {
  psommet_t s;

  s = g;

  while ((s != NULL) && (s->label != label)) {
    s = s->sommet_suivant;
  }
  return s;
}

parc_t existence_arc(parc_t l, psommet_t s) {
  parc_t p = l;

  while (p != NULL) {
    if (p->dest == s) return p;
    p = p->arc_suivant;
  }
  return p;
}

void ajouter_arc(psommet_t o, psommet_t d, int distance) {
  parc_t parc;

  parc = (parc_t)malloc(sizeof(arc_t));

  if (existence_arc(o->liste_arcs, d) != NULL) {
    fprintf(stderr, "ajout d'un arc deja existant\n");
    exit(-1);
  }

  parc->poids = distance;
  parc->dest = d;
  parc->arc_suivant = o->liste_arcs;
  parc->deja_parcouru = 0;
  o->liste_arcs = parc;
  return;
}

// ===================================================================

int nombre_sommets(pgraphe_t g) {
  psommet_t p = g;
  int nb = 0;

  while (p != NULL) {
    nb = nb + 1;
    p = p->sommet_suivant;
  }

  return nb;
}

int nombre_arcs(pgraphe_t g) {
  psommet_t p = g;
  int nb_arcs = 0;

  while (p != NULL) {
    parc_t l = p->liste_arcs;

    while (l != NULL) {
      nb_arcs = nb_arcs + 1;
      l = l->arc_suivant;
    }

    p = p->sommet_suivant;
  }
  return nb_arcs;
}

void init_couleur_sommet(pgraphe_t g) {
  psommet_t p = g;

  while (p != NULL) {
    p->couleur = 0;         // couleur indefinie
    p = p->sommet_suivant;  // passer au sommet suivant dans le graphe
  }

  return;
}

int colorier_graphe(pgraphe_t g) {
  /*
    coloriage du graphe g

    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g;
  parc_t a;
  int couleur;
  int max_couleur = INT_MIN;  // -INFINI

  int change;

  init_couleur_sommet(g);

  while (p != NULL) {
    couleur = 1;  // 1 est la premiere couleur

    // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

    // Choix de la couleur pour le sommet p

    do {
      a = p->liste_arcs;
      change = 0;

      while (a != NULL) {
        if (a->dest->couleur == couleur) {
          couleur = couleur + 1;
          change = 1;
        }
        a = a->arc_suivant;
      }

    } while (change == 1);

    // couleur du sommet est differente des couleurs de tous les voisins

    p->couleur = couleur;
    if (couleur > max_couleur) max_couleur = couleur;

    p = p->sommet_suivant;
  }

  return max_couleur;
}

void afficher_graphe_largeur(pgraphe_t g, int r) {
  pfile_t f = creer_file();
  psommet_t tmp = chercher_sommet(g, r);
  enfiler(f, tmp);
  while (!file_vide(f)) {
    tmp = defiler(f);
    if (!tmp->deja_parcouru) printf("%d", tmp->label);
    tmp->deja_parcouru = 1;
    parc_t arc = tmp->liste_arcs;
    while (arc != NULL) {
      if (!arc->dest->deja_parcouru) {
        enfiler(f, arc->dest);
      }
      arc = arc->arc_suivant;
    }
  }
}

void afficher_graphe_profondeur_V2(pgraphe_t g, int r) {
  pgraphe_t start = NULL;
  pgraphe_t courant = g;
  // initialisation des champs deja_connu de chaque sommets a faux
  if (courant != NULL) {
    while (courant->sommet_suivant != NULL) {
      if (courant->label == r) {
        start = courant;
      }
      courant->deja_parcouru = 0;
      courant = courant->sommet_suivant;
    }
    if (start == NULL) {
      start = courant;
    }
    courant->deja_parcouru = 0;
    parcour_profondeur_V2(start);
    courant = g;
    while ((courant != NULL)) {
      if (!(courant->deja_parcouru)) {
        parcour_profondeur_V2(courant);
      }
      courant = courant->sommet_suivant;
    }
  }
}

void parcour_profondeur_V2(pgraphe_t g) {
  if (g == NULL) {
    return;
  }
  if (!g->deja_parcouru) {
    g->deja_parcouru = 1;
    printf("Sommet : %d parcouru\n", g->label);
  }
  parc_t courant = g->liste_arcs;
  while ((courant != NULL) && (courant->arc_suivant != NULL)) {
    if (!courant->deja_parcouru) {
      courant->deja_parcouru = 1;
      parcour_profondeur_V2(courant->dest);
    }
    courant = courant->arc_suivant;
  }
}

void afficher_graphe_profondeur2(pgraphe_t g, int r) {
  psommet_t tmp = chercher_sommet(g, r);
  afficher_graphe_profondeur_rec(tmp);
  return;
}

void afficher_graphe_profondeur_rec(pgraphe_t g) {
  if (g == NULL || g->deja_parcouru) return;
  printf("Sommet : %d parcouru\n", g->label);
  g->deja_parcouru = 1;
  parc_t arc = g->liste_arcs;
  while (arc != NULL) {
    afficher_graphe_profondeur_rec(arc->dest);
    arc = arc->arc_suivant;
  }
  return;
}

void afficher_graphe_profondeur(pgraphe_t g, int r) {
  /*
    afficher les sommets du graphe avec un parcours en profondeur
  */
  ppile_t f = creer_pile();
  psommet_t tmp = chercher_sommet(g, r);
  empiler(f, tmp);
  while (!pile_vide(f)) {
    tmp = depiler(f);
    if (!tmp->deja_parcouru) printf("Sommet : %d parcouru\n", tmp->label);
    tmp->deja_parcouru = 1;
    parc_t arc = tmp->liste_arcs;
    while (arc != NULL) {
      if (!arc->dest->deja_parcouru) {
        empiler(f, arc->dest);
      }
      arc = arc->arc_suivant;
    }
  }
  return;
}

void algo_dijkstra(pgraphe_t g, int r) {
  psommet_t start = chercher_sommet(g, r);
  if (start == NULL) {
    printf("Le sommet demandé : %d n'existe pas !\n", r);
    return;
  }
  start->etiq = 0;
  psommet_t next = traitement_dijkstra(start);
  while (next != NULL) {
    next = traitement_dijkstra(next);
  }
  debugDijikstra(g, r);
  return;
}

psommet_t traitement_dijkstra(psommet_t sommet) {
  parc_t arc_courant = sommet->liste_arcs;
  psommet_t next_traitement = NULL;
  while (arc_courant != NULL) {
    if (arc_courant->dest->etiq > arc_courant->poids + sommet->etiq) {
      arc_courant->dest->etiq = arc_courant->poids + sommet->etiq;
      if ((next_traitement == NULL) ||
          (next_traitement->etiq > arc_courant->poids + sommet->etiq)) {
        next_traitement = arc_courant->dest;
      }
    }
    arc_courant = arc_courant->arc_suivant;
  }
  sommet->traite = 1;
  if (next_traitement == NULL || next_traitement->traite) {
    return NULL;
  }
  return next_traitement;
}

void debugDijikstra(pgraphe_t g, int r) {
  psommet_t sommet_courant = g;
  printf("LANCE AVEC LE SOMMET : %d\n", r);
  while (sommet_courant != NULL) {
    printf("Sommet : %d , etiq : %d\n", sommet_courant->label,
           sommet_courant->etiq);
    sommet_courant = sommet_courant->sommet_suivant;
  }
}

// ======================================================================

int degre_sortant_sommet(pgraphe_t g, psommet_t s) {
  /*
    Cette fonction retourne le nombre d'arcs sortants
    du sommet n dans le graphe g
  */
  psommet_t parcours = g;
  while (parcours != s) {
    if (parcours == NULL) return 0;
    parcours = parcours->sommet_suivant;
  }
  int arc_sortant = 0;
  parc_t arc = parcours->liste_arcs;
  while (arc != NULL) {
    arc_sortant++;
    arc = arc->arc_suivant;
  }
  return arc_sortant;
}

int degre_entrant_sommet(pgraphe_t g, psommet_t s) {
  /*
    Cette fonction retourne le nombre d'arcs entrants
    dans le noeud n dans le graphe g
  */
  int arc_entrant = 0;
  while (g != NULL) {
    parc_t arc = g->liste_arcs;
    while (arc != NULL) {
      if (arc->dest == s) arc_entrant++;
      arc = arc->arc_suivant;
    }
    g = g->sommet_suivant;
  }
  return arc_entrant;
}

int degre_maximal_graphe(pgraphe_t g) {
  /*
    Max des degres des sommets du graphe g
  */
  int max = 0;
  int tmp;
  psommet_t s = g;
  while (s != NULL) {
    tmp = degre_entrant_sommet(g, s) + degre_sortant_sommet(g, s);
    if (tmp > max) max = tmp;
    s = s->sommet_suivant;
  }
  return max;
}

int degre_minimal_graphe(pgraphe_t g) {
  int min = INT_MAX;
  psommet_t courant = g;
  while (courant != NULL) {
    int tmp =
        degre_entrant_sommet(g, courant) + degre_sortant_sommet(g, courant);
    if (tmp < min) {
      min = tmp;
    }
    courant = courant->sommet_suivant;
  }
  return min;
}

int independant(pgraphe_t g) {
  /* Les aretes du graphe n'ont pas de sommet en commun */
  if (g == NULL) return 1;
  if (g->liste_arcs != NULL) {
    if (g->liste_arcs->arc_suivant != NULL) return 0;
    if (g->liste_arcs->dest->liste_arcs != NULL &&
        g->liste_arcs->dest->liste_arcs->dest != g)
      return 0;
  }
  return independant(g->sommet_suivant);
}

int complet(pgraphe_t g) {
  psommet_t s = g;
  int nb_sommet = 0;
  while (s != NULL) {
    nb_sommet++;
    s = s->sommet_suivant;
  }
  s = g;
  int tmp;
  while (s != NULL) {
    parc_t arc = s->liste_arcs;
    tmp = 0;
    while (arc != NULL) {
      if (arc->dest != s) tmp++;
      arc = arc->arc_suivant;
    }
    if (tmp != nb_sommet - 1) return 0;
    s = s->sommet_suivant;
  }
  return 1;
}

int regulier(pgraphe_t g) {
  /*
     graphe regulier: tous les sommets ont le meme degre
     g est le ponteur vers le premier sommet du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */
  if (degre_maximal_graphe(g) == degre_minimal_graphe(g)) return 1;
  return 0;
}

/*
  placer les fonctions de l'examen 2017 juste apres
*/
