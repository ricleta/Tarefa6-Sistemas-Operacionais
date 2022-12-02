// Eduardo Dantas Luna, 2111484
// Ricardo Bastos Leta Vieira, 2110526

#include "simulador.h"

int main(int argc, char * argv[])
{
  int page_size, mem_size, n_pages, page_id, page_ids_size;
  int n_written = 0;
  int n_page_faults = 0;
  int index_to_overwrite;
  Page_opt *pages;
  Page_opt *previsao;
  int pages_current_size = 0;
  int *page_ids;
  int time = 0;
  FILE *arq;
  unsigned int addr;
  char rw;
  
  if (argc < 4)
  {
    puts("4 argumentos necessarios");
    exit(0);
  }

  arq = fopen(argv[1], "r");
  
  if (arq == NULL)
  {
    perror("arquivo de log nao encontrado");
    exit(2);
  }
  
  if (8 > atoi(argv[2]) || atoi(argv[2]) > 32)
  {
    perror("tamanho de pagina invalido, deve ser entre 8 e 32");
    exit(3);
  }

  if (1 > atoi(argv[3]) || atoi(argv[3]) > 16)
  {
    perror("tamanho de memoria fisica invalido, deve ser entre 1 e 16");
    exit(4);
  }
  
  page_size = atoi(argv[2]);
  mem_size = atoi(argv[3]);
  n_pages = (mem_size * 1000)/ page_size;
  pages = (Page_opt *) malloc(sizeof(Page_opt) * pow(2, 32 - (int)(ceil(log2(page_size*1000)))));
  page_ids = (int *) malloc(sizeof(int) * n_pages);
  
  if (pages == NULL)
  {
    perror("erro no malloc");
    exit(5);
  }

  previsao = (Page_opt *) malloc(sizeof(Page_opt) * 1000000);
  
  ler_futuro(arq, page_size, previsao);
  
  // printf("Executando simulador...\n");
  // while(fscanf(arq, "%x %c ", &addr, &rw) == 2)
  // {
  //     page_id = addr >> (int)(ceil(log2(page_size * 1000)));
    
  //     if(!is_in_Pages(pages,page_id,pages_current_size))
  //     { 
  //       if(pages_current_size >= n_pages)
  //       {
  //         // ######Chamada pode estar errada, verificar dps#######
  //         index_to_overwrite = opt(pages,page_id,n_pages);
  //         set_page(pages,index_to_overwrite,page_id,time, rw);
  //         page_ids[pages_current_size] = index_to_overwrite;
          
  //         n_written++;
  //     	} 
  //     	else 
  //     	{
  //       	set_page(pages,pages_current_size,page_id,time, rw);
  //       	page_ids[pages_current_size] = page_id;
  //       	pages_current_size++;
  //     	}
        
  //    	n_page_faults++;
  //    }

  //   time++;
  // }

  // printf("Arquivo de entrada: %s\n", argv[2]);
  // printf("Tamanho da memoria fisica: %s MB\n", argv[4]);
  // printf("Tamanho das paginas: %s KB\n", argv[3]);
  // printf("Algoritmo de substituicao: %s \n", argv[1]);
  // printf("Numero de page faults: %d \n",n_page_faults);
  // printf("Numero de paginas escritas: %d \n",n_written);

  fclose(arq);
  free(pages);
  free(page_ids);
  
  return 0;
}