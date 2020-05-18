#include <stdlib.h>

#include "a234.h"
#include "file.h"

pfile_t creer_file ()
{
  pfile_t f=malloc(sizeof(file_t));
  f->tete=-1;
  f->queue=0;
  return f;
}

int detruire_file (pfile_t f)
{
  free(f);
  return 0;
}




int file_vide (pfile_t f)
{
  if(f->tete==-1)return 1;
  return 0;
}

int file_pleine (pfile_t f)
  {
  if(f->queue==f->tete)return 1;
  return 0;
}

pnoeud234 defiler (pfile_t f)
  {
  if(!file_vide(f)){
    pnoeud234 tmp=f->Tab[f->tete];
    f->tete=(f->tete+1)%MAX_FILE_SIZE;
    if(f->tete==f->queue)f->tete=-1;
    return tmp;
  }else return NULL;
}

int enfiler (pfile_t f, pnoeud234 p)
{
  if(p==NULL)return 1;
  if(!file_pleine(f)){
    f->Tab[f->queue]=p;
    if(f->tete==-1)f->tete=f->queue;
    f->queue=(f->queue+1)%MAX_FILE_SIZE;
    return 0;
  }else return 1;
}
