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

typedef struct _page_opt
{
  int R; // 0 para false, 1 para true
  int M; // 0 para false, 1 para true
  int t_future_accesses[10000];
  int id;
  int n_access;
} Page_opt;


int * page_ids_arr(int tam) 
{
	int *arr = (int *) malloc(sizeof(int) * tam);

	for(int i = 0; i < tam; i++)
  {
    arr[i] = -1;      
  }

	return arr;
}

void init_previsao(Page_opt * arr, int tam) 
{
	for(int i = 0; i < tam; i++)
  {
    arr[0].n_access = 0;
    arr[0].M = -1;
    arr[0].R = -1; 
  }
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

void set_page_opt(Page_opt * pages, int id, int last_access, char RW)
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

  pages[id].t_future_accesses[pages[id].n_access] = last_access;
  pages[id].M = M;
  pages[id].R = R;

  pages[id].n_access++;
}

void ler_futuro(FILE *arq, int page_size, Page_opt *previsao)
{
  int page_id, pages_current_size, n_pages;
  int time = 0;
  char rw;
  unsigned int addr;

  init_previsao(previsao, 1000000);
  
  while(fscanf(arq, "%x %c ", &addr, &rw) == 2)
  {
    page_id = addr >> (int)(ceil(log2(page_size * 1000))); 
    set_page_opt(previsao, page_id, time, rw);          
        
    time++;
  }
}

int get_menor_tempo_valido(int *arr, int tam, int t_atual)
{
  int menor = 0;
  
  for (int i = 0; i < tam; i++)
  {
    if (arr[i] < menor || arr[i] > t_atual)
    {
       menor = arr[i];   
    }
  }

  return menor;
}

int opt(Page * pages, Page_opt * previsao, int page_id,int n_pages, int time, int *page_ids)
{
  int mais_distante = -1;
  int id_mais_distante = -1;
  int aux = 0;

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
  	int t_futura; 
    int pos_futura = 0; 
  	
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
  	
  	// vet contém todos os índices de um dos critérios acima
  	// caso exista mais de um elemento no vetor, tirar o mais antigo
  	pos_futura = 0;
  	index_in_pages = page_ids[vet[0]];
  	t_futura = pages[index_in_pages].t_last_access;
  	
  	for(int i = 1; i < tam ; i++) 
    {
  		index_in_pages = page_ids[vet[i]];
  		aux = get_menor_tempo_valido(previsao[pages[i].id].t_future_accesses,previsao[pages[i].id].n_access,time );
      
      if (t_futura < aux) 
      {
  			pos_futura = vet[i];
  			t_futura = aux;
  		}
  	}

    free(no_ref_no_mod); 
    free(mod_no_ref); 
    free(ref_no_mod); 
    free(ref_mod);
  
    return pos_futura;
  // for (int i = 0; i < n_pages; i++)
  // {
  //   aux = get_menor_tempo_valido(previsao[pages[i].id].t_future_accesses,previsao[pages[i].id].n_access,time );  
  //   if (aux > mais_distante)
  //   {
  //     mais_distante = aux;
  //     id_mais_distante = pages[i].id;
  //   }
  // }
  
  // return id_mais_distante;
}

/*
page id = 123
t_access = [3, 6, 9]

page id = 456
t_access = [4, 7, 8]

time = 1
123 -> 3
456 -> 4 ##

time = 5
123 -> 9 ##
456 -> 8 

time = 8
123 -> 9
456 -> 10 ###
*/