// Eduardo Dantas Luna, 2111484
// Ricardo Bastos Leta Vieira, 2110526

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _page
{
  int R; // 0 para false, 1 para true
  int M; // 0 para false, 1 para true
  int t_last_access;
  int id;
} Page;

int * page_ids_arr(int tam) 
{
	int *arr = (int *) malloc(sizeof(int) * tam);

	for(int i = 0; i < tam; i++)
  {
    arr[i] = -1;      
  }

	return arr;
}

int is_in_Pages(Page * vector, int id,int len)
{
  if(len == 0)
  {
    return 0;
  }
  
  for(int i = 0; i< len;i++)
  {
    if(vector[i].id==id)
    {
      return 1;
    }
  }
  
  return 0;
}

void set_page(Page * pages, int index, int id, int last_access, char RW)
{
  int R;
  int M;

  if(RW == 'R') 
  {
    R = 1;
    M = 0;
  }
  else if(RW == 'W')
  {
    R = 1;
    M = 1;    
  }
  
  pages[index].id = id;
  pages[index].t_last_access = last_access;
  pages[index].M = M;
  pages[index].R = R;
}

int lru(Page * pages,int page_id,int n_pages)
{
  int min_id = pages->id;
  int min_t = pages->t_last_access;
  
  for(int i = 1; i < n_pages ; i++)
  {
    if(min_t > pages[i].t_last_access)
    { //se for menor q o atual
      min_t = pages[i].t_last_access; //atualiza o id do menor e o tempo do menor
      min_id = i;
    }
  }
  
  //retorna qual deve ser sobrescrito
  return min_id;
}

int nru(Page * pages,int *page_ids, int n_pages)
{
  	int index_in_pages, flag, tam;
    int * no_ref_no_mod; // array de paginas nao referenciadas e nao modificadas
    int * mod_no_ref; // array de paginas nao referenciadas mas modificadas
    int * ref_no_mod; // array de paginas referenciadas mas nao modificadas
    int * ref_mod; // array de paginas referenciadas e modificadas
  
  	int id_arr0 = 0; // indice atual de no_ref_no_mod
    int id_arr1 = 0; // indice atual de mod_no_ref
    int id_arr2 = 0; // indice atual de ref_no_mod
    int id_arr3 = 0; // indice atual de ref_mod

    // tempo e posição da página mais antiga
  	int t_antiga; 
    int pos_antiga = 0; 
  	
  	no_ref_no_mod = page_ids_arr(n_pages); 
  	mod_no_ref = page_ids_arr(n_pages); 
  	ref_no_mod = page_ids_arr(n_pages); 
  	ref_mod = page_ids_arr(n_pages);

  	for (int i = 0; i < n_pages; i++) 
    {
  		index_in_pages = page_ids[i];

  		if (pages[index_in_pages].R == 0) 
      {
  			if(pages[index_in_pages].M == 0) 
        {
  				no_ref_no_mod[id_arr0] = i;
  				id_arr0++;
  			}
  			else 
        {
  				mod_no_ref[id_arr1] = i;
  				id_arr1++;
  			}
  		} 
  		else 
      {
  			if(pages[index_in_pages].M == 0) 
        {
  				ref_no_mod[id_arr2] = i;
  				id_arr2++;
  			}
  			else 
        {
  				ref_mod[id_arr3] = i;
  				id_arr3++;
  			}
  		}
  	}
  
  	int * vet;
  	if ( no_ref_no_mod[0] != -1)
    {
  		vet = no_ref_no_mod;
  		tam = id_arr0;
  	} 
  	else if (mod_no_ref[0] != -1) 
    {
  		vet = mod_no_ref;
  		tam = id_arr1;
  	} 
  	else if (ref_no_mod[0] != -1) 
    {
  		vet = ref_no_mod;
  		tam = id_arr2;
  	} 
  	else 
    {
  		vet = ref_mod;
  		tam = id_arr3;
  	}
  	
  	// vet contém todos os índices de vp de um dos critérios acima
  	// caso exista mais de um elemento no vetor, tirar o mais antigo
  	pos_antiga = 0;
  	index_in_pages = page_ids[vet[0]];
  	t_antiga = pages[index_in_pages].t_last_access;
  	
  	for(int i = 1; i < tam ; i++) 
    {
  		index_in_pages = page_ids[vet[i]];
  		
      if (t_antiga > pages[index_in_pages].t_last_access) 
      {
  			pos_antiga = vet[i];
  			t_antiga = pages[index_in_pages].t_last_access;
  		}
  	}

    free(no_ref_no_mod); 
    free(mod_no_ref); 
    free(ref_no_mod); 
    free(ref_mod);
  
    return pos_antiga;
}
