#include <stdio.h>
#include <string.h>
#include <ctype.h>
// #include <stdlib.h> //usada para automatizar os códigos, terminar a função depois 
#include <unistd.h>

#define ARQUIVO_USUARIO "usuario.csv"
#define ARQUIVO_LIVRO "livro.csv"
#define ARQUIVO_AUTOR "autor.csv"
#define ARQUIVO_TEMP "temp.csv"
#define MAX_NOME 80
#define ID 100

typedef struct{
	char autor01[MAX_NOME],autor02[MAX_NOME],autor03[MAX_NOME];
}Nomeautores; //struct para usar na função relacionar_id_autor 

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
Nomeautores relacionar_id_autor(int autor1, int autor2, int autor3);
void listar_usuarios();
void listar_autores();
void listar_livro();
void atualizar_usuario();

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

 fprintf(usuario, "%s;%d\n", u.nome_usuario, u.id_usuario);
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

 fprintf(autor, "%s;%d\n", a.nome_autor, a.id_autor);
 fclose(autor);
}

int id_l = 100; //id único para cada livro
void cadastrar_livro(){
 Livro l;
 memset(&l, 0, sizeof(l));
 FILE *livro = fopen(ARQUIVO_LIVRO, "a");
 int opcao; //usado para guardar as opções 1 - Sim , 2 - Não
 int i; //usada para percorrer o vetor do id de autores

 if(livro == NULL){ 
     printf("Erro ao abir %s", ARQUIVO_LIVRO);
	 return;
    }

 printf("Título 🔽\n");
 fgets(l.nome_livro, MAX_NOME, stdin);
 l.nome_livro[strcspn(l.nome_livro, "\n")] = '\0';

 do{
     listar_autores();
     printf("Encontrou seu(s) autor(es)?\n"
           "1 - Sim!\n"
           "2 - Não!\n");
     scanf(" %d", &opcao);

     if(opcao != 1 && opcao != 2){
         printf("Digite uma opção válida!\n"
               "Aguarde...");
         sleep(2);
         limpar_tela();
        }
     else if(opcao == 2){
         cadastrar_autor();
         limpar_tela();
        }
    }while(opcao != 1);  

 for(i = 0; i < 3; i++){
     printf("Digite o código do %dº autor 🔽\n", i + 1);
     scanf(" %d", &l.id_autores[i]);

     if(i == 2){
         limpar_tela();
         break;
        }

     do{
         printf("Deseja adicionar mais algum autor?\n"
               "1 - Sim!\n"
               "2 - Não!\n");
         scanf(" %d", &opcao);
         if(opcao != 1 && opcao != 2){
             printf("Digite uma opção válida!\n"
                    "Aguarde...");
             sleep(2);
             limpar_tela();
            }
        }while(opcao != 1 && opcao != 2);

        limpar_tela();
        if(opcao == 2) break; 
		 
    }


 l.id_livro = id_l; //adicionando código do livro
 id_l += 1;

 fprintf(livro, "%s;%d;%d|%d|%d\n", l.nome_livro, l.id_livro, l.id_autores[0], l.id_autores[1], l.id_autores[2]);
 fclose(livro);

}
 
/*Função para relacionar o autor com seu código*/

Nomeautores relacionar_id_autor(int autor1, int autor2, int autor3){ 
 Autor a;
 Nomeautores n;
 memset(&n, 0, sizeof(n));
 char linha [300];
 FILE *autor = fopen(ARQUIVO_AUTOR, "r");

 if(autor == NULL){
	 printf("Erro ao abrir %s",ARQUIVO_AUTOR);
	 return;
    }
	
 fgets(linha, sizeof(linha),autor);
 
 while(fscanf(autor, "%[^;];%d\n", a.nome_autor, &a.id_autor) == 2){
     if(autor1 == a.id_autor){
		 strcpy(n.autor01, a.nome_autor);
	    }
	 else if(autor2 == a.id_autor){
		 strcpy(n.autor02, a.nome_autor);
	    }
	 else if(autor3 == a.id_autor){
		 strcpy(n.autor03, a.nome_autor);
	    }
    }

 fclose(autor);
 return n;
}

/*Funções para listar os objetos*/

void listar_usuarios(){
 Usuario u;
 char linha [300];
 FILE *usuario = fopen(ARQUIVO_USUARIO, "r");

 if(usuario == NULL){
 	 printf("Erro ao abrir o arquivo %s",ARQUIVO_USUARIO);
	 return;
    }

 fgets(linha, sizeof(linha), usuario); //pula o cabeçalho

 printf("-------------------USUÁRIOS CADASTRADOS----------------🔽\n");
 printf("|%-10s | %-28s | %-10s |\n", "ID", "NOME", "STATUS");
 printf("|-----------|------------------------------|------------|\n");

 while(fscanf(usuario, "%[^;];%d;%[^;]\n", u.nome_usuario, u.id_usuario, u.status) == 3){
	 printf("|%-10d | %-28s | %-10s |\n", u.id_usuario, u.nome_usuario, u.status);
    }

 fclose(usuario);
}

void listar_autores(){
 Autor a;
 char linha[300];
 FILE *autor = fopen(ARQUIVO_AUTOR, "r");

 fgets(linha, sizeof(linha), autor); // Pula o cabeçalho

 printf("------------AUTORES CADASTRADOS---------- 🔽\n");
 printf("|%-10s | %-29s|\n", "ID", "NOME");
 printf("|-----------|------------------------------|\n");

 while( fscanf(autor, "%[^;];%d\n", a.nome_autor, &a.id_autor) == 2){
	 printf("%-10d|%-29s\n", a.id_autor,a.nome_autor);


    }

  fclose(autor);
}

void listar_livro(){
 Livro l;
 Nomeautores n;
 memset(&l, 0,sizeof(l)); //Todos os campos da struct são inicializados com o caracter '\0' 
 memset(&n, 0, sizeof(n)); 
 char linha[300];

 FILE *livro = fopen(ARQUIVO_LIVRO,"r");
 
 if(livro == NULL){
	 printf("Erro ao abrir %s", ARQUIVO_LIVRO);
	 return;
    }

 fgets(linha, sizeof(linha), livro); //pula o cabeçalho

     printf("------------------------------LIVROS CADASTRADOS------------------------------ 🔽\n");
    printf("|%-6s | %-25s | %-20s | %-20s | %-20s |\n", "ID", "TITULO", "AUTOR 1", "AUTOR 2", "AUTOR 3");
    printf("|-------|---------------------------|----------------------|----------------------|----------------------|\n");

 while(fscanf(livro, "%[^;];%d;%d|%d|%d\n", l.nome_livro, &l.id_livro, &l.id_autores[0], &l.id_autores[1], &l.id_autores[2] ) == 5){
     n = relacionar_id_autor(l.id_autores[0],l.id_autores[1],l.id_autores[2]);
	 if(n.autor01[0] == '\0') strcpy(n.autor01, "Vazio");
	 if(n.autor02[0] == '\0') strcpy(n.autor02, "Vazio");
	 if(n.autor03[0] == '\0') strcpy(n.autor03, "Vazio"); 
	 printf("%-6d | %-25s | %-20s | %-20s | %-20s\n", l.id_livro, l.nome_livro, n.autor01, n.autor02, n.autor03);
	 
    }


 fclose(livro);

}

void atualizar_usuario(){
   Usuario u;
   FILE *usuario = fopen(ARQUIVO_USUARIO, "r");
   FILE *temp = fopen(ARQUIVO_TEMP, "w");
   char linha[300];
   int id, opcao, atualizou = 0, encontrou = 0;

   if(usuario == NULL){
	 printf("Erro ao abrir %s",ARQUIVO_USUARIO);
	 return;
   }
   if(temp == NULL){
	 printf("Erro ao abrir %s",ARQUIVO_TEMP);
	 return;
   }

   limpar_buffer();

   fgets(linha, sizeof(linha), usuario);//pula o cabeçallho
   fputs(linha, temp); //pega o cabeçalho de linha e coloca no arquivo temporário

   printf("Digite o id do usuário 🔽\n");
   scanf("%d",&id);
    
  while(fscanf(usuario, "%[^;];%d;%[^\n]\n", u.nome_usuario, &u.id_usuario, u.status) == 3){
     if(id == u.id_usuario){
		 encontrou = 1;
         printf("-------------------USUÁRIO ENCONTRADO----------------🔽\n");
         printf("|%-10s | %-28s | %-10s |\n", "ID", "NOME", "STATUS");
         printf("|-----------|------------------------------|------------|\n");
		 printf("|%-10d | %-28s | %-10s |\n\n",u.id_usuario, u.nome_usuario, u.status);
	     do{
		     printf("Deseja mudar alguma informação?\n"
			    "1 - Sim\n"
			    "2 - Não\n");
		     scanf(" %d", &opcao);

		     if(opcao != 1 && opcao != 2){ 
			     printf("Digite uma opção válida!\n"
			        "Aguarde...");
			     limpar_tela();
		    	}
            }while(opcao != 1 && opcao != 2);
		  if(opcao == 1){
		     limpar_tela();
			 limpar_buffer();
		     printf("Insira o novo nome 🔽\n");
		     fgets(u.nome_usuario, MAX_NOME, stdin);
		     u.nome_usuario[strcspn(u.nome_usuario, "\n")] = '\0';
		     printf("Insira o novo status 🔽\n");
		     fgets(u.status, MAX_NOME, stdin);
		     u.status[strcspn(u.status, "\n")] = '\0';

			 printf("-------------------USUÁRIO ATUALIZADO----------------🔽\n");
             printf("|%-10s | %-28s | %-10s |\n", "ID", "NOME", "STATUS");
             printf("|-----------|------------------------------|------------|\n");
	         printf("|%-10d | %-28s | %-10s |\n\n",u.id_usuario, u.nome_usuario, u.status);

			 fprintf(temp, "%s;%d;%s\n", u.nome_usuario, u.id_usuario, u.status );

			 atualizou = 1;
            }			 
		  else if(opcao == 2) fprintf(temp, "%s;%d;%s\n", u.nome_usuario, u.id_usuario, u.status );
		}
		else fprintf(temp, "%s;%d;%s\n", u.nome_usuario, u.id_usuario, u.status );
    }

  fclose(usuario);
  fclose(temp);

  if(encontrou){
     if(atualizou){
	     remove(ARQUIVO_USUARIO);
	     rename(ARQUIVO_TEMP,ARQUIVO_USUARIO);
        }
     else remove(ARQUIVO_TEMP);
    }
	else{
	 remove(ARQUIVO_TEMP);
     printf("Usuário não encontrado!");
	}
	   
}







int main(){
	garantir_arquivos();
    int opcao;
	while (1){
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



}