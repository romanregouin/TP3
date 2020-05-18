#include <stdio.h>
#include <stdlib.h>
#include "a234.h"
#include "pile.h"

ppile_t creer_pile ()
{
  ppile_t p;
  p = malloc(sizeof(pile_t));
  if(p==NULL){
    printf("Erreur allocation\n");
    exit(-1);
  }
  p->sommet = 0;
  return p ;
}

int detruire_pile (ppile_t p)
{
  free(p);
  return 0;
}  

int pile_vide (ppile_t p)
{
  return(p->sommet==0);
}

int pile_pleine (ppile_t p)
{
  return(p->sommet==MAX_PILE_SIZE);
} 

pnoeud234 depiler (ppile_t p)
{
  if(p==NULL){
    printf("Erreur Pile Vide\n");
    return NULL;
  }
  if(!pile_vide(p)){
    p->sommet--;
    return p->Tab[p->sommet];
  }else return NULL;
}

int empiler (ppile_t p, pnoeud234 pn)
{
  if(!pile_pleine(p)){
    p->Tab[p->sommet] = pn;
    p->sommet++;
    return 0;
  }
  return 1; 
}
