#include <stdio.h>
#include <stdlib.h>  //usado system
#include <ctype.h>   //usado toupper
#include <string.h>  //usado strcmp
#include <locale.h>

int contador = 0;

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
  char titulo[100];
  int LivroExiste;

  do {
      system("cls");

      printf("*** inclusao ***\n\n");
      printf("Título: ");
      setbuf(stdin, NULL);
      gets(titulo);

      //clean_stdin(RgLivro.Titulo);
      strcpy(RgLivro.Titulo, titulo);

      //Impossibilita fármacos repetidos
      strcpy(LivroParaVerificar, RgLivro.Titulo);
      LivroExiste = VerificarLivro(LivroParaVerificar);

      if (LivroExiste == 1){
          printf("\nLivro com esse título já existe!\n\n");
          system("read -p \"Pressione enter para sair\" saindo");
          system("pause");
          break;
     };

     strcpy(RgLivro.Titulo, titulo);

      printf("Nome do Autor: ");
      gets(RgLivro.Autor);

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
  contador = 0;
  char titulo[100][100];
  char autor[100][100];
  int paginas[100];
  int quantidade[100];
  int status[100];
  int x, y, r;
  int i = 0;
  char auxTitulo[80];
  char auxAutor[80];
  int auxPaginas;
  int auxQuantidade;
  int auxStatus;

  fseek(ArqLivro,0,0);

  do{
  	fread(&RgLivro,Tamanho,1,ArqLivro);
  	contador++;
  }while (!feof(ArqLivro));

  fseek(ArqLivro,0,0);
    i = 0;
  do{
  	 fread(&RgLivro,Tamanho,1,ArqLivro);
  	 strcpy(titulo[i], RgLivro.Titulo);
  	 strcpy(autor[i], RgLivro.Autor);
  	 paginas[i] = RgLivro.QtdPaginas;
  	 quantidade[i] = RgLivro.QtdLivrosDisponiveis;
  	 status[i] = RgLivro.Status;
  	 i++;
  }while (!feof(ArqLivro));

  system("cls");
  printf("*** lista todos ***\n\n");


   if(contador == 2){

 	    for(i = 0; i< 1; i++){

        	printf("Título: %s\n", titulo[i]);
  	        printf("Autor: %s\n", autor[i]);
            printf("Quantidade de Páginas: %d\n", paginas[i]);
            printf("Quantidade de Livros Disponíveis: %d\n", quantidade[i]);
            if ( quantidade[i] == 0 ){
                printf("Status do Livro: %s\n\n", "Indisponivel");
            } else {
            printf("Status do Livro: %s\n\n", "Disponivel");

            }
        }

   }else if(contador == 3){

 	    fseek(ArqLivro,0,0);

    	for(x=0; x<= contador - 1;x++){
		    for(y = x+1; y<= 3; y++){
			    r = strcmp(titulo[x], titulo[y]);

			    if(r > 0){
			    	strcpy(auxTitulo, titulo[x]);
			    	strcpy(titulo[x], titulo[y]);
				    strcpy(titulo[y], auxTitulo);

				    strcpy(auxAutor, autor[x]);
			    	strcpy(autor[x], autor[y]);
				    strcpy(autor[y], auxAutor);

				    auxPaginas = paginas[x];
			    	paginas[x] = paginas[y];
				    paginas[y] = auxPaginas;

				    auxQuantidade = quantidade[x];
			    	quantidade[x] = quantidade[y];
				    quantidade[y] = auxQuantidade;

				    auxStatus = status[x];
			    	status[x] = status[y];
				    status[y] = auxStatus;
			    }
            }
        }




      	for(i = 1; i<contador; i++){

        	printf("Título: %s\n", titulo[i]);
  	        printf("Autor: %s\n", autor[i]);
            printf("Quantidade de Páginas: %d\n", paginas[i]);
            printf("Quantidade de Livros Disponíveis: %d\n", quantidade[i]);
            if ( quantidade[i] == 0 ){
                printf("Status do Livro: %s\n\n", "Indisponivel");
            } else {
            printf("Status do Livro: %s\n\n", "Disponivel");

            }

        }

 }else if(contador >3){

 	 fseek(ArqLivro,0,0);

    	for(x=0; x<= contador - 1;x++){
		    for(y = x+1; y<= 2; y++){
			    r = strcmp(titulo[x], titulo[y]);

			    if(r > 0){
			    	strcpy(auxTitulo, titulo[x]);
			    	strcpy(titulo[x], titulo[y]);
				    strcpy(titulo[y], auxTitulo);

				    strcpy(auxAutor, autor[x]);
			    	strcpy(autor[x], autor[y]);
				    strcpy(autor[y], auxAutor);

				    auxPaginas = paginas[x];
			    	paginas[x] = paginas[y];
				    paginas[y] = auxPaginas;

				    auxQuantidade = quantidade[x];
			    	quantidade[x] = quantidade[y];
				    quantidade[y] = auxQuantidade;

				    auxStatus = status[x];
			    	status[x] = status[y];
				    status[y] = auxStatus;
			    }
            }
        }




      	for(i = 0; i<contador -1; i++){

        	printf("Título: %s\n", titulo[i]);
  	        printf("Autor: %s\n", autor[i]);
            printf("Quantidade de Páginas: %d\n", paginas[i]);
            printf("Quantidade de Livros Disponíveis: %d\n", quantidade[i]);
            if ( quantidade[i] == 0 ){
                printf("Status do Livro: %s\n\n", "Indisponivel");
            } else {
            printf("Status do Livro: %s\n\n", "Disponivel");

            }

        }
 }

    system("pause");
    system("read -p \"Pressione enter para sair\" saindo");
    return;
}

void LTodosDisponiveis() {

    contador = 0;
  char titulo[100][100];
  char autor[100][100];
  int paginas[100];
  int quantidade[100];
  int status[100];
  int x, y, r;
  int i = 0;
  char auxTitulo[80];
  char auxAutor[80];
  int auxPaginas;
  int auxQuantidade;
  int auxStatus;

  fseek(ArqLivro,0,0);

  do{
  	fread(&RgLivro,Tamanho,1,ArqLivro);
  	contador++;
  }while (!feof(ArqLivro));

  fseek(ArqLivro,0,0);
    i = 0;
  do{
  	 fread(&RgLivro,Tamanho,1,ArqLivro);
  	 strcpy(titulo[i], RgLivro.Titulo);
  	 strcpy(autor[i], RgLivro.Autor);
  	 paginas[i] = RgLivro.QtdPaginas;
  	 quantidade[i] = RgLivro.QtdLivrosDisponiveis;
  	 status[i] = RgLivro.Status;
  	 i++;
  }while (!feof(ArqLivro));

  system("cls");
  printf("*** lista todos ***\n\n");


   if(contador == 2){

 	    for(i = 0; i< 1; i++){

        	if ( quantidade[i] != 0 ){
        	printf("Título: %s\n", titulo[i]);
  	        printf("Autor: %s\n", autor[i]);
            printf("Quantidade de Páginas: %d\n", paginas[i]);
            printf("Quantidade de Livros Disponíveis: %d\n", quantidade[i]);
            printf("Status do Livro: %s\n\n", "Disponivel");
            }
        }

   }else if(contador == 3){

 	    fseek(ArqLivro,0,0);

    	for(x=0; x<= contador - 1;x++){
		    for(y = x+1; y<= 3; y++){
			    r = strcmp(titulo[x], titulo[y]);

			    if(r > 0){
			    	strcpy(auxTitulo, titulo[x]);
			    	strcpy(titulo[x], titulo[y]);
				    strcpy(titulo[y], auxTitulo);

				    strcpy(auxAutor, autor[x]);
			    	strcpy(autor[x], autor[y]);
				    strcpy(autor[y], auxAutor);

				    auxPaginas = paginas[x];
			    	paginas[x] = paginas[y];
				    paginas[y] = auxPaginas;

				    auxQuantidade = quantidade[x];
			    	quantidade[x] = quantidade[y];
				    quantidade[y] = auxQuantidade;

				    auxStatus = status[x];
			    	status[x] = status[y];
				    status[y] = auxStatus;
			    }
            }
        }




      	for(i = 1; i<contador; i++){

        	if ( quantidade[i] != 0 ){
        	printf("Título: %s\n", titulo[i]);
  	        printf("Autor: %s\n", autor[i]);
            printf("Quantidade de Páginas: %d\n", paginas[i]);
            printf("Quantidade de Livros Disponíveis: %d\n", quantidade[i]);
            printf("Status do Livro: %s\n\n", "Disponivel");
            }

        }

 }else if(contador >3){

 	 fseek(ArqLivro,0,0);

    	for(x=0; x<= contador - 1;x++){
		    for(y = x+1; y<= 2; y++){
			    r = strcmp(titulo[x], titulo[y]);

			    if(r > 0){
			    	strcpy(auxTitulo, titulo[x]);
			    	strcpy(titulo[x], titulo[y]);
				    strcpy(titulo[y], auxTitulo);

				    strcpy(auxAutor, autor[x]);
			    	strcpy(autor[x], autor[y]);
				    strcpy(autor[y], auxAutor);

				    auxPaginas = paginas[x];
			    	paginas[x] = paginas[y];
				    paginas[y] = auxPaginas;

				    auxQuantidade = quantidade[x];
			    	quantidade[x] = quantidade[y];
				    quantidade[y] = auxQuantidade;

				    auxStatus = status[x];
			    	status[x] = status[y];
				    status[y] = auxStatus;
			    }
            }
        }




      	for(i = 0; i<contador -1; i++){

        	if ( quantidade[i] != 0 ){
        	printf("Título: %s\n", titulo[i]);
  	        printf("Autor: %s\n", autor[i]);
            printf("Quantidade de Páginas: %d\n", paginas[i]);
            printf("Quantidade de Livros Disponíveis: %d\n", quantidade[i]);
            printf("Status do Livro: %s\n\n", "Disponivel");
            }

        }
 }

    system("pause");
    system("read -p \"Pressione enter para sair\" saindo");
    return;
}

void Atualizar(){

	char titulo[80];
	char tituloAtualizado[80];
	char tituloNovo[80][80];
	char autorNovo[80][80];
	int paginasNovo[80];
	int quantidadeNovo[80];
	int statusNovo[80];
	char autor[80];
	int paginas;
	int quantidade;
	int status;
	int existeLivro = 0;
	int opcao;
	int i = 0;

	//calculado contador
	contador = 0;
	fseek(ArqLivro,0,0);
	    do{
	        fread(&RgLivro,Tamanho,1,ArqLivro);
	        contador++;

	    }while (!feof(ArqLivro));
	system("cls");
	printf("Digite o título do livro que deseja atualizar: ");
	setbuf(stdin, NULL);
	gets(titulo);

	fseek(ArqLivro,0,0);
	do{
		fread(&RgLivro,Tamanho,1,ArqLivro);
		if(strcmp(RgLivro.Titulo, titulo)==0){

		existeLivro++;


		}

	}while (!feof(ArqLivro));


	if(existeLivro > 0){
		    system("cls");
		    printf("Escolha o tipo de atualização\n");
		    printf("1 - Atualizar título\n");
		    printf("2 - Atualizar Autor\n");
		    printf("3 - Atualizar número de páginas\n");
		    printf("4 - Atualizar quantidade de páginas\n");
		    printf("5 - Atualizar status\n");
		    scanf("%d", &opcao);

		    switch(opcao){

		    	case 1:{
		    		int Achou = 0;
		    		fclose(ArqLivro);
                    ArqLivro=fopen("Livros.dat","r+b");

                    do {
	                    fread(&RgLivro,Tamanho,1,ArqLivro);
	                    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	                        Achou=1;
	                }}
                    while (!feof(ArqLivro)&&(Achou==0));
                        if (Achou==0)
                            printf("Registro inexistente!");
                        else{
                            printf("Qual o novo titulo? \n");
                            setbuf(stdin, NULL);
                            gets(RgLivro.Titulo);
                            fseek(ArqLivro,-Tamanho,1);
                            fwrite(&RgLivro,Tamanho,1,ArqLivro);
                            printf(">>> Alteracao efetuada com sucesso! <<<\n");}
                            system("pause");
                }break;

				case 2:{
					gets(autor);
					int Achou = 0;
		    		fclose(ArqLivro);
                    ArqLivro=fopen("Livros.dat","r+b");

                    do {
	                    fread(&RgLivro,Tamanho,1,ArqLivro);
	                    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	                        Achou=1;
	                }}
                    while (!feof(ArqLivro)&&(Achou==0));
                        if (Achou==0)
                            printf("Registro inexistente!");
                        else{
                            printf("Qual o novo autor? \n");
                            setbuf(stdin, NULL);
                            gets(RgLivro.Autor);
                            fseek(ArqLivro,-Tamanho,1);
                            fwrite(&RgLivro,Tamanho,1,ArqLivro);
                            printf(">>> Alteracao efetuada com sucesso! <<<\n");}
                            system("pause");
				}break;

				case 3:{
					int Achou = 0;
		    		fclose(ArqLivro);
                    ArqLivro=fopen("Livros.dat","r+b");

                    do {
	                    fread(&RgLivro,Tamanho,1,ArqLivro);
	                    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	                        Achou=1;
	                }}
                    while (!feof(ArqLivro)&&(Achou==0));
                        if (Achou==0)
                            printf("Registro inexistente!");
                        else{
                            printf("Qual o novo número de páginas? \n");
                            scanf("%d", &RgLivro.QtdPaginas);
                            fseek(ArqLivro,-Tamanho,1);
                            fwrite(&RgLivro,Tamanho,1,ArqLivro);
                            printf(">>> Alteracao efetuada com sucesso! <<<\n");}
                            system("pause");
				}break;

				case 4:{
					int Achou = 0;
		    		fclose(ArqLivro);
                    ArqLivro=fopen("Livros.dat","r+b");

                    do {
	                    fread(&RgLivro,Tamanho,1,ArqLivro);
	                    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	                        Achou=1;
	                }}
                    while (!feof(ArqLivro)&&(Achou==0));
                        if (Achou==0)
                            printf("Registro inexistente!");
                        else{
                            printf("Qual a nova quantidade de livros? \n");
                            scanf("%d", &RgLivro.QtdLivrosDisponiveis);
                            fseek(ArqLivro,-Tamanho,1);
                            fwrite(&RgLivro,Tamanho,1,ArqLivro);
                            printf(">>> Alteracao efetuada com sucesso! <<<\n");}
                            system("pause");
				}break;

				case 5:{
					int Achou = 0;
		    		fclose(ArqLivro);
                    ArqLivro=fopen("Livros.dat","r+b");

                    do {
	                    fread(&RgLivro,Tamanho,1,ArqLivro);
	                    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	                        Achou=1;
	                }}
                    while (!feof(ArqLivro)&&(Achou==0));
                        if (Achou==0)
                            printf("Registro inexistente!");
                        else{
                            printf("Qual o novo status? \n");
                            scanf("%d", &RgLivro.Status);
                            fseek(ArqLivro,-Tamanho,1);
                            fwrite(&RgLivro,Tamanho,1,ArqLivro);
                            printf(">>> Alteração efetuada com sucesso! <<<\n");}
                            system("pause");
				}break;

				default : {
					printf("opção inválida\n");
				}
				break;
			}

	}else{
		printf("Livro não encontrado\n");
		system("pause");
	}

}

void Consultar() {
  system("cls");
  printf("*** consulta ***\n\n");
  fseek(ArqLivro,0,0);
  printf("Qual o título do livro a consultar? ");
  char titulo[20];
  setbuf(stdin, NULL);
  gets(titulo);

  int Achou=0;
  do {
	fread(&RgLivro,Tamanho,1,ArqLivro);
	if (strcmp(RgLivro.Titulo, titulo)==0 ){
	  Achou=1;
	  printf("\nTítulo: %s\n",RgLivro.Titulo);
      printf("Autor: %s\n", RgLivro.Autor);
      printf("Quantidade de Páginas: %d\n", RgLivro.QtdPaginas);
      printf("Quantidade de Livros Disponíveis: %d\n",RgLivro.QtdLivrosDisponiveis);
      if ( RgLivro.QtdLivrosDisponiveis <= 0 ){
        printf("Status do Livro: %s\n", "Indisponivel");
      } else {
        printf("Status do Livro: %s\n", "Disponivel");


      }
      printf("***\n\n");}}
    while (!feof(ArqLivro)&&(Achou==0));
  if (Achou==0)
    printf("Livro inexistente!\n");
  system("pause");
  return;
  }

  void Reservar() {
    system("cls");
    printf("*** reserva ***\n\n");

    char titulo[80];
    int Achou = 0;
	fclose(ArqLivro);
    ArqLivro=fopen("Livros.dat","r+b");
    printf("Qual o título do livro a reservar? ");
    setbuf(stdin, NULL);
    gets(titulo);

    do {
	    fread(&RgLivro,Tamanho,1,ArqLivro);
	    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	        Achou=1;
	    }

		}while (!feof(ArqLivro)&&(Achou==0));

			if (Achou==0){

				printf("Registro inexistente!\n");
				system("pause");
			} else{

                if(RgLivro.QtdLivrosDisponiveis <= 0){

                printf(">>> Indisponível para reserva! <<<\n");
                system("pause");
				}else{

					//scanf("%d", &RgLivro.QtdLivrosDisponiveis );
					RgLivro.QtdLivrosDisponiveis = RgLivro.QtdLivrosDisponiveis - 1;
                    fseek(ArqLivro,-Tamanho,1);
                    fwrite(&RgLivro,Tamanho,1,ArqLivro);
                    printf(">>> Reserva efetuada com sucesso! <<<\n");
				}
                system("pause");

			}
  }


    void Devolver() {
    system("cls");
    printf("*** devolução ***\n\n");

    char titulo[80];
    int Achou = 0;
	fclose(ArqLivro);
    ArqLivro=fopen("Livros.dat","r+b");
    printf("Qual o título do livro a devolver? ");
    setbuf(stdin, NULL);
    gets(titulo);

    do {
	    fread(&RgLivro,Tamanho,1,ArqLivro);
	    if (strcmp(RgLivro.Titulo, titulo)==0 ){
	        Achou=1;
	    }

		}while (!feof(ArqLivro)&&(Achou==0));

			if (Achou==0){

				printf("Registro inexistente!\n");
				system("pause");
			} else{

					//scanf("%d", &RgLivro.QtdLivrosDisponiveis );
					RgLivro.QtdLivrosDisponiveis = RgLivro.QtdLivrosDisponiveis + 1;
                    fseek(ArqLivro,-Tamanho,1);
                    fwrite(&RgLivro,Tamanho,1,ArqLivro);
                    printf(">>> Devolução efetuada com sucesso! <<<\n");

                system("pause");

			}
  }

int main(){

   setlocale(LC_ALL, "");
       ArqLivro=fopen("Livros.dat","a+b");
   char Opcao;

   //	Atualizando o contador;
    int i = 0;
    fseek(ArqLivro,0,0);

    do{
  	    fread(&RgLivro,Tamanho,1,ArqLivro);
  	    contador++;
    }while (!feof(ArqLivro));

  do{
	  system("cls");
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
      case 'A': Atualizar(); break;
      case 'C': Consultar(); break;
      case 'R': Reservar(); break;
      case 'L': Devolver(); break;
      }
    } while (Opcao != 'S');

  fclose(ArqLivro);

  return 0;
}
