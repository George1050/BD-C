#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"


/* IMPORTANT change this line to setup connection */
#define DBDATA "host=localhost dbname=BD_CADQUEST user=postgres password=12031997";
////////////////
//QUERY GLOBAL//
////////////////
char query[150];
/////////////////////
//Variaveis Globais//
/////////////////////
const char *conninfo;
    PGconn     *conn;
	PGresult   *res;
	int         nFields;
	int q = 1;
//////////////////////////////////
//Listar todas as questoes no BD//
//////////////////////////////////
void listar(){
	int i,j;
	///////////////////////////////////////////////////////////////
	//Seleção das questoes mostrando a pergunta, dominio e o tema//
	///////////////////////////////////////////////////////////////
	res = PQexec(conn,query);
	switch (PQresultStatus(res)) {
		case PGRES_COMMAND_OK: printf("ok\n"); break;
		case PGRES_EMPTY_QUERY: printf("empty"); break;
		case PGRES_TUPLES_OK: 
			nFields = PQnfields(res);
		    for (i = 0; i < nFields; i++)
		    printf("\n");
		    /* next, print out the rows */
		    for (i = 0; i < PQntuples(res); i++)
		    {
		    	printf("Questao %d\n",i+1);
				q++;
		        printf("------------------------------------------------------\n");
				//printf("%s ", PQfname(res, i));	
		        for (j = 0; j < nFields; j++)
					printf("-->%s \n", PQgetvalue(res, i, j));
		        printf("------------------------------------------------------\n");
		    }	break;
		
		case PGRES_BAD_RESPONSE: printf("error: bad response"); break;
		case PGRES_NONFATAL_ERROR: 
		case PGRES_FATAL_ERROR: printf(PQresultErrorMessage(res)); break;
		default:
			printf("Algo inesperado");
	}
}
//////////////////////////////////////////
//BUSCA E MOSTRA TODOS OS DOMINIOS NO BD//
//////////////////////////////////////////
///////////////////////////////////////
//BUSCA E MOSTRA TODOS OS TEMAS NO BD//
///////////////////////////////////////
void listar_DomTema(){
	int i,j;
	res = PQexec(conn,query);
	switch (PQresultStatus(res)) {
		case PGRES_COMMAND_OK: printf("ok\n"); break;
		case PGRES_EMPTY_QUERY: printf("empty"); break;
		case PGRES_TUPLES_OK: 
			nFields = PQnfields(res);
		    for (i = 0; i < PQntuples(res); i++)
		    {
		        for (j = 0; j < nFields; j++)
		            printf("-->%s ", PQgetvalue(res, i, j));
		        printf("\n");
		    }	break;
		
		case PGRES_BAD_RESPONSE: printf("error: bad response"); break;
		case PGRES_NONFATAL_ERROR: 
		case PGRES_FATAL_ERROR: printf(PQresultErrorMessage(res)); break;
		default:
			printf("Algo inesperado");
	}
}void cadastrar(){
	res = PQexec(conn,query);
	switch (PQresultStatus(res)) {
		case PGRES_COMMAND_OK: printf("ok\n"); break;
		case PGRES_EMPTY_QUERY: printf("empty"); break;
		case PGRES_TUPLES_OK: nFields = PQnfields(res);break;
		case PGRES_BAD_RESPONSE: printf("error: bad response"); break;
		case PGRES_NONFATAL_ERROR: 
		case PGRES_FATAL_ERROR: printf(PQresultErrorMessage(res)); break;
		default:
			printf("Algo inesperado");
	}
}

static void exit_nicely(PGconn *conn){
    PQfinish(conn);
    exit(1);
}
////////////////////////////////////////////////
//////////   FUNÇÃO PRINCIPAL   ////////////////
////////////////////////////////////////////////
int main(int argc, char **argv){

    //PARA CADASTRAR
	char pergunta[400], resposta[400], dominio, dificuldade;	
	int tema[5] = {0};
	int opcao;
	if (argc > 1)
        conninfo = argv[1];
    else
        conninfo = DBDATA;
		
    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
            PQerrorMessage(conn));
        exit_nicely(conn);
    }
    //////////////
	//MEU CODIGO//
	//////////////
	int busca = 0, op, voltas = 0;
	char sair;
	do{
		printf("\n\t\t\tEscolha uma das opcoes:\n");
		printf("============================================================================\n");
		printf("\t1.cadastrar \t2.listar \t3.buscar \t4.sair\n");
		printf("============================================================================\n>>");
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				/////////////////////////////////
				//CADASTRA NOVAS QUESTOES NO BD//
				/////////////////////////////////
				printf("Cadastrando...\n");
				setbuf(stdin, NULL);
				//////////////////////////////////////
				//LOOP PARA CADASTRAR NOVOS DOMINIOS//
				//////////////////////////////////////
				printf("============================================================================\n");
				do{
					sprintf(query,"SELECT * FROM dominio;");
					listar_DomTema();
					printf("\nInforme o Dominio da Questao pelo numero indicado:\nNao encontrou o Dominio certo digite 'C' para cadastrar\n>>");
					scanf("%c",&dominio);
					setbuf(stdin, NULL);
						if(dominio == 'c'){
							printf("Digite o Dominio: ");
							char dominioN[50];
							gets(dominioN);
							sprintf(query,"INSERT INTO dominio (dominio) VALUES ('%s');",dominioN);
							cadastrar();
						}
					setbuf(stdin, NULL);
				}while(dominio == 'c');
				/////////////////////////////
				//LOOP PARA CADASTRAR TEMAS//
				/////////////////////////////
				printf("============================================================================\n");
				do{
					sprintf(query,"SELECT id_tema, tema FROM tema WHERE fk_dominio = '%c';",dominio);
					listar_DomTema();
					printf("\nInforme o Tema da Questao pelo numero indicado: \nObservacao uma questao so pode ter no maximo"
							"5 temas e a apenas um dominio.\n"
							"Nao encontrou o Tema certo digite '0' para cadastrar.\n>>");
					scanf("%d",&op);
					setbuf(stdin, NULL);
					if(op == '0'){
						printf("Digite o Tema: ");
						char temaN[100];
						gets(temaN);
						sprintf(query,"INSERT INTO tema (tema,fk_dominio) VALUES ('%s','%c');",temaN,dominio);
						cadastrar();
					}else{
						tema[voltas] = op;
						voltas++;
						system("cls");
					}
					if(sair != 's'){
						printf("Deseja continuar a escolher temas, digite f para ficar e s para sair: ");
						scanf("%c",&op);
						setbuf(stdin, NULL);
					}
				}while(sair != 's');	
					printf("============================================================================\n");
					printf("Escolha a Dificuldade: \n 1.Facil 2.Medio 3.Dificil\n>>");
					scanf("%c",&dificuldade);
					setbuf(stdin, NULL);
				printf("============================================================================\n"
						"Escreva a Pergunta: \n>>");
				gets(pergunta);
				printf("============================================================================\n");
				printf("Escreva a Resposta: \n>>");
				gets(resposta);
				printf("Obrigado pela sua atencao\n");
				setbuf(stdin, NULL);
				printf("============================================================================\n");
				sprintf(query,"SELECT * FROM questoes;");
				listar();
				sprintf(query, "INSERT INTO questoes (fk_dominio,fk_dificuldade,pergunta,resposta) VALUES ('%c','%c','%s','%s');",dominio,dificuldade,pergunta,resposta);	
			    cadastrar();
			    for(int i = 0; i<voltas; i++){
			    	if(tema[i] != 0){
						sprintf(query, "INSERT INTO quest_tema VALUES (%d,'%c');",q,tema[i]);
			    		cadastrar();
					}
				}
				system("cls");
				printf("============================================================================\n");
				break;
			case 2:
				/////////////////////////////////
				//LISTA TODAS AS QUESTOES DO BD//
				/////////////////////////////////
				sprintf(query,"SELECT dominio.dominio, questoes.pergunta, questoes.resposta FROM questoes JOIN dominio ON dominio.id_dominio = questoes.fk_dominio;");
    			listar();
    			printf("\n");
				break;
			case 3:
				////////////////////////////////////////////
				//BUSCA NO BD POR DOMINIO, TEMA ou PALAVRA// 
				//TODAS AS QUESTOES QUE FOREM PARECIDAS/////
				//BUSCA NO BD POR DOMINIO, TEMA ou PALAVRA// 
				//TODAS AS QUESTOES QUE FOREM PARECIDAS/////
				////////////////////////////////////////////
				printf("Voce pode pesquisar por: \n1.Texto da questao, 2.Dominio, 3.Tema, 4.Dificuldade ou 5.Sair\n>>");
				printf("============================================================================\n>>");
				scanf("%d",&busca);
				setbuf(stdin, NULL);
				char comando[150];
				if(busca == 0){
					system("cls");
					sprintf(query,"SELECT questoes.pergunta, dominio.dominio, tema.tema FROM questoes JOIN dominio ON dominio.id_dominio = questoes.fk_dominio JOIN tema ON tema.id_tema = questoes.fk_tema;");
    				listar();
				}else if(busca == 1){
					printf("Digite o que voce quer Buscar: \n>>");
					gets(comando);
					system("cls");
					printf("============================================================================\n");
					sprintf(query,"SELECT pergunta, resposta FROM questoes WHERE pergunta LIKE '%s';",comando);
					printf("============================================================================\n");
					listar();
				}else if(busca == 2){
					setbuf(stdin, NULL);
					printf("============================================================================\n");
					sprintf(query,"SELECT * FROM dominio;");
					listar_DomTema();
					printf("============================================================================\n");
					printf("\nInforme o Dominio da Questao pelo numero indicado: \n>>");
					gets(comando);
					system("cls");
					sprintf(query,"SELECT pergunta, resposta FROM questoes WHERE fk_dominio = '%s';",comando);
					printf("============================================================================\n");
					listar();
				}else if(busca == 3){
					setbuf(stdin, NULL);
					printf("============================================================================\n");
					sprintf(query,"SELECT * FROM tema;");
					listar_DomTema();
					printf("============================================================================\n");
					printf("\nInforme o Tema da Questao pelo numero indicado: \n>>");
					gets(comando);
					system("cls");
					sprintf(query,"SELECT questoes.pergunta, questoes.resposta FROM quest_tema JOIN questoes ON id_questao = fk_idquestao JOIN tema ON id_tema = fk_idtema WHERE fk_idtema = '%s';",comando);
					printf("============================================================================\n");
					listar();
				}else if(busca == 4){
					setbuf(stdin, NULL);
					sprintf(query,"SELECT * FROM dificuldade;");
					listar_DomTema();
					printf("============================================================================\n");
					printf("\nInforme a Dificuldade da Questao pelo numero indicado: \n>>");
					gets(comando);
					system("cls");
					sprintf(query,"SELECT * FROM questoes WHERE fk_dificuldade = '%s';",comando);
					printf("============================================================================\n");
					listar();
				}else if(busca == 5){
					system("cls");
					printf("Vlw");
				}
				printf("\n");
				break;
			case 4:
				////////
				//SAIR//
				////////
				printf("============================================================================\n");
				printf("Vlw");
				break;
			default:
				printf("Invalido");
		}
	}while(opcao != 4);
	return 0;
}
