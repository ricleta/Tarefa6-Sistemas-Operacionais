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
  int t_last_future_access;
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

void set_page(Page_opt * pages, int index, int id, int last_access, char RW)
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
  
  pages[index].t_last_future_access = last_access;
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
  
  pages[id].t_last_future_access = last_access;
  pages[id].M = M;
  pages[id].R = R;
}

void ler_futuro(FILE *arq, int page_size, Page_opt *pages)
{
  int addr, page_id, pages_current_size, n_pages;
  int time = 0;
  // int *page_ids = page_ids_arr(1000000);
  char rw;
  
  while(fscanf(arq, "%x %c ", &addr, &rw) == 2)
  {
    page_id = addr >> (int)(ceil(log2(page_size * 1000))); 
    set_page_opt(pages, page_id, time, rw);          
    
    // printf("t = %d\n", time);
    // printf("addr = %x\n", addr);
    // printf("Page id = %d\n", page_id);
    // printf("last access = %d\n", pages[page_id].t_last_future_access);
    
    time++;
  }
}

int opt(Page * pages,int page_id,int n_pages)
{
  // TODO
  return -1;
}
