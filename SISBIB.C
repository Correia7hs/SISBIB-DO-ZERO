#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> //usada para automatizar os códigos, terminar a função depois 

#define ARQUIVO_USUARIO "usuario.csv"
#define ARQUIVO_LIVRO "livro.csv"
#define ARQUIVO_AUTOR "autor.csv"
#define MAX_NOME 80
#define ID 100

typedef struct{
	char nome_usuario[MAX_NOME];
    int id_usuario;
	char status[20];
}Usuario;

typedef struct{
	char nome_livro[MAX_NOME];
	int id_livro;
    int id_autores[3];
}Livro;

typedef struct{
	char nome_autor[MAX_NOME];
	int id_autor;
}Autor;



void garantir_arquivos();
void limpar_buffer();
void limpar_tela();
void cadastrar_usuario();
void cadastrar_autor();
void cadastrar_livro();
void listar_autores();

void garantir_arquivos(){
  FILE *usuario = fopen(ARQUIVO_USUARIO, "r");
  FILE *livro = fopen(ARQUIVO_LIVRO, "r");
  FILE *autor = fopen(ARQUIVO_AUTOR, "r");

 if(usuario == NULL || livro == NULL || autor == NULL){
	 if(usuario == NULL){
         FILE *usuario = fopen(ARQUIVO_USUARIO, "w");
		 if(usuario != NULL){
             fprintf(usuario, "%s;%s;%s\n", "nome", "id", "status");
		     fclose(usuario);
		    }
	    }
	 if(livro == NULL){
		 FILE *livro = fopen(ARQUIVO_LIVRO, "w");
		 if(livro != NULL){
			 fprintf(livro, "%s;%s;%s\n", "nome", "id", "idautores");
			 fclose(livro);
		    }
	    }
     if(autor == NULL){
	     FILE *autor = fopen(ARQUIVO_AUTOR, "w");
		 if(autor != NULL){
			 fprintf(autor, "%s;%s;%s\n", "nome", "id");
			 fclose(autor);
		    }

    	}
	
    }

 if(usuario != NULL || livro != NULL || autor != NULL){
	   if(usuario != NULL){
	     fclose(usuario);
        }
	   if(livro != NULL){
         fclose(livro);
	    }
	   if(autor != NULL){
	     fclose(autor);	
	    }

    }

}

void limpar_buffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF ){}
}

void limpar_tela(void) {
    printf("\033[2J\033[H");  /* limpa a tela e posiciona o cursor no topo */
}


int id_u = 100; //id único para cada usuário
void cadastrar_usuario(){
 Usuario u;
 FILE *usuario = fopen(ARQUIVO_USUARIO, "a"); //modo append para adicionar informações 
 
 printf("Nome do usuário 🔽\n");
 fgets(u.nome_usuario, MAX_NOME, stdin);
 u.nome_usuario[strcspn(u.nome_usuario, '\n')] = '\0';

 
 u.id_usuario = id_u;
 id_u += 1;

 fprintf(usuario, "%s;%d", u.nome_usuario, u.id_usuario);
 fclose(usuario);

}

int id_a = 100; //id único para cada autor
void cadastrar_autor(){
 Autor a;
 FILE *autor = fopen(ARQUIVO_AUTOR, "a");
 
 printf("Nome do autor 🔽\n");
 fgets(a.nome_autor, MAX_NOME, stdin);
 a.nome_autor[strcspn(a.nome_autor, '\n')] = '\0';

 a.id_autor = id_a;
 id_a += 1;

 fprintf(autor, "%s;%d", a.nome_autor, a.id_autor);
 fclose(autor);
}

int id_l = 100; //id único para cada livro
void cadastrar_livro(){
 Livro l;
 FILE *livro = fopen(ARQUIVO_LIVRO, "a");

 printf("Título 🔽\n");
 fgets(l.nome_livro, MAX_NOME, stdin);
 l.nome_livro[strcspn(l.nome_livro, '\n')] = '\0';

 listar_autores();

 //Terminar função para alocar os autores aos livros

 l.id_livro = id_l; //adicionando código do livro
 id_l += 1;

 fprintf(livro, "%s;%d;%d|%d|%d\n", l.nome_livro, l.id_livro, l.id_autores[0], l.id_autores[1], l.id_autores[2]);
 fclose(livro);

}
 
/*Funções para listar os objetos*/

void listar_autores(){
 Autor a;
 int id, achou = 0;
 char linha[300];
 FILE *autor = fopen(ARQUIVO_AUTOR, "r");

 fgets(linha, sizeof(linha), autor); // Pula o cabeçalho

 printf("|%-10s | %-30s|\n", "ID", "NOME");
printf("|-----------|------------------------------|\n");

 while( fscanf(autor, "%[^;];%d", a.nome_autor, &a.id_autor) == 2){
	 printf("%-10d|%-30s", a.id_autor,a.nome_autor);


    }

  fclose(autor);
}


int main(){
	garantir_arquivos();
    int opcao;
    printf("+++++++++++++++++++++++++++++++++++++++++++++ \n"
	       "|SISBB - SISTEMA DE GESTÃO DE BIBLIOTECAS 🕮| \n"
	       "+++++++++++++++++++++++++++++++++++++++++++++ \n"
	       "1. Gestão de livros \n"
           "2. Gestão de autores \n"
	       "3. Gestão de usuários \n"
	       "4. Gestão de empréstimos \n"
	       "5. Relatórios \n"
	       "6. Sair \n"
	       "↑ Escolha uma opção acima ↑ \n");
    scanf(" %d", &opcao);
}