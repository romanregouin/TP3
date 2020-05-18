#ifndef _PILE_H_
#define _PILE_H_
#include "graphe.h"
#define MAX_PILE_SIZE 64

typedef struct
{
  int sommet;
  psommet_t Tab[MAX_PILE_SIZE];
} pile_t, *ppile_t;

ppile_t creer_pile();

int detruire_pile(ppile_t p);

int pile_vide(ppile_t p);

int pile_pleine(ppile_t p);

psommet_t depiler(ppile_t p);

int empiler(ppile_t p, psommet_t pn);

#endif