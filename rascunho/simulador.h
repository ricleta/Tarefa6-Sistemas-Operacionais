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

int opt(Page * pages,int page_id,int n_pages)
{
  // TODO
  return -1;
}
