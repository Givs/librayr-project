#include <stdio.h>
#include <stdlib.h>  //usado system
#include <ctype.h>   //usado toupper
#include <string.h>  //usado strcmp

struct TpLivro{
	char Titulo[20];
  char Autor[20];
  int QtdPaginas;
	int QtdLivrosDisponiveis;
  int Status;
  };
  
typedef struct TpLivro TpLIVRO;

TpLIVRO RgLivro;
  
FILE *ArqLivro;

long int Tamanho= 40 * sizeof(char) + 3 * sizeof(int);

long int TArquivo(){
	fseek(ArqLivro, 0, 2);
	long int R=ftell(ArqLivro)/Tamanho;
	return R;
}


int VerificarLivro(char * str){
  if (TArquivo() != 0){
    int Achou = 0;
    fseek(ArqLivro, 0, 0);

    do {
            fread(&RgLivro, Tamanho, 1, ArqLivro);
            if (strcmp(RgLivro.Titulo, str) == 0){
                Achou = 1;
            }
        } while (!feof(ArqLivro) && (Achou == 0));

    if (Achou == 0){
        return 0; //0 - não existe registro com esse nome
    } else {
        return 1; //1 - já existe registro com esse nome
    } 
  }
  return 0;
}

void Incluir() {
  char R;
  char LivroParaVerificar[20];
  int LivroExiste;

  do {
      system("clear");

      printf("*** inclusao ***\n\n");

      printf("Título: ");
      scanf("%s",RgLivro.Titulo);
      //clean_stdin(RgLivro.Titulo);


      //Impossibilita fármacos repetidos
      strcpy(LivroParaVerificar, RgLivro.Titulo);
      LivroExiste = VerificarLivro(LivroParaVerificar);

      if (LivroExiste == 1){
          printf("\nLivro com esse título já existe!\n\n");
          system("read -p \"Pressione enter para sair\" saindo");
          break;
      };

      printf("Nome do Autor: ");
      scanf("%s", RgLivro.Autor);

      printf("Quantidade de Páginas: ");
      scanf("%d", &RgLivro.QtdPaginas);

      printf("Quantidade de Livros Disponíveis: ");
      scanf("%d",&RgLivro.QtdLivrosDisponiveis);

      if ( RgLivro.QtdLivrosDisponiveis > 0 ){  
        RgLivro.Status = 1;
      } else {
        RgLivro.Status = 0;
      }
      
      fseek(ArqLivro,0,2);
      fwrite(&RgLivro,Tamanho,1,ArqLivro);

      printf("\nNova inclusao? S/N ");
      scanf(" %c",&R);
      R=toupper(R);
    } while (R!='N');

  return;
}

void LTodos() {
  system("clear");
  printf("*** lista todos ***\n\n");  
  fseek(ArqLivro,0,0);

  do {
    fread(&RgLivro,Tamanho,1,ArqLivro);

    if (!feof(ArqLivro)){
      printf("Título: %s\n",RgLivro.Titulo);
      printf("Autor: %s\n", RgLivro.Autor);
      printf("Quantidade de Páginas: %d\n", RgLivro.QtdPaginas);
      printf("Quantidade de Livros Disponíveis: %d\n",RgLivro.QtdLivrosDisponiveis);
      if ( RgLivro.Status == 0 ){
        printf("Status do Livro: %s\n", "Indisponivel");
      } else {
        printf("Status do Livro: %s\n", "Disponivel");
      }
      printf("***\n\n");
    }
  } while (!feof(ArqLivro));

  system("read -p \"Pressione enter para sair\" saindo");
  return;
}

void LTodosDisponiveis() {
  system("clear");
  printf("*** Lista Todos Livros Disponíveis***\n\n");  
  fseek(ArqLivro,0,0);

  do {
    fread(&RgLivro,Tamanho,1,ArqLivro);

    if (!feof(ArqLivro)){
      if (RgLivro.Status != 0){
        printf("Título: %s\n",RgLivro.Titulo);
        printf("Autor: %s\n", RgLivro.Autor);
        printf("Quantidade de Páginas: %d\n", RgLivro.QtdPaginas);
        printf("Quantidade de Livros Disponíveis: %d\n",RgLivro.QtdLivrosDisponiveis);
        if ( RgLivro.Status == 0 ){
          printf("Status do Livro: %s\n", "Indisponivel");
        } else {
          printf("Status do Livro: %s\n", "Disponivel");
        }
        printf("***\n\n");
      }
    }
  } while (!feof(ArqLivro));

  system("read -p \"Pressione enter para sair\" saindo");
  return;
}

int main(){

  ArqLivro=fopen("Livros.dat","a+b");
  char Opcao;

  do{
	  system("clear");

    printf("\n\n> > > Pague Pouco < < < \n\n");
    printf("Que deseja fazer? \n\n");
    printf("I - Cadastrar Livro \n");  
    printf("T - Listar Todos os Livros \n");
    printf("D - Listar Todos os Livros Disponíveis \n");
    printf("A - Atualizar Informações de um Livro \n");
    printf("C - Consultar Informações de um Livro \n");
    printf("R - Reservar um Livro \n");
    printf("L - Devolver um Livro \n");
    printf("S - Sair \n\n");

    scanf(" %c", &Opcao);
    Opcao=toupper(Opcao);

    switch (Opcao){
      case 'I': Incluir(); break;
      case 'T': LTodos(); break;
      case 'D': LTodosDisponiveis(); break;
      }
    } while (Opcao != 'S');

  fclose(ArqLivro);

  return 0;
}