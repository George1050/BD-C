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
		            printf(" %s ", PQgetvalue(res, i, j));
		        printf("\n");
		    }	break;
		
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
	char pergunta[400], resposta[400], dominio, tema, dificuldade;	
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
	int busca = 0;
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
				setbuf(stdin, NULL);
				printf("============================================================================\n");
				sprintf(query,"SELECT * FROM dominio;");
				listar_DomTema();
				printf("\nInforme o Dominio da Questao pelo numero indicado: ");
				scanf("%c",&dominio);
				setbuf(stdin, NULL);
				printf("============================================================================\n");
				sprintf(query,"SELECT * FROM tema;");
				listar_DomTema();
				printf("\nInforme o Tema da Questao pelo numero indicado: ");
				scanf("%c",&tema);
				setbuf(stdin, NULL);
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
				sprintf(query, "INSERT INTO questoes (fk_dominio,fk_tema,pergunta,resposta,fk_dificuldade) VALUES ('%c','%c','%s','%s','%c');",dominio,tema,pergunta,resposta,dificuldade);	
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
				printf("============================================================================\n");
				break;
			case 2:
				/////////////////////////////////
				//LISTA TODAS AS QUESTOES DO BD//
				/////////////////////////////////
				sprintf(query,"SELECT questoes.pergunta, dominio.dominio, tema.tema FROM questoes JOIN dominio ON dominio.id_dominio = questoes.id_dominio JOIN tema ON tema.id_tema = questoes.id_tema;");
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
				printf("Voce pode pesquisar por: \n1.Texto da questao, 2.Dominio, 3.Tema ou 4.Sair\n>>");
				printf("============================================================================\n>>");
				scanf("%d",&busca);
				setbuf(stdin, NULL);
				char comando[150];
				if(busca == 0){
					sprintf(query,"SELECT questoes.pergunta, dominio.dominio, tema.tema FROM questoes JOIN dominio ON dominio.id_dominio = questoes.id_dominio JOIN tema ON tema.id_tema = questoes.id_tema;");
    				listar();
				}else if(busca == 1){
					printf("Digite o que voce quer Buscar: \n>>");
					gets(comando);
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
					sprintf(query,"SELECT pergunta, resposta FROM questoes WHERE id_dominio = '%s';",comando);
					printf("============================================================================\n");
					listar();
				}else if(busca == 3){
					setbuf(stdin, NULL);
					printf("============================================================================\n");
					sprintf(query,"SELECT * FROM tema;");
					listar_DomTema();
					printf("============================================================================\n");
					printf("\nInforme o Dominio da Questao pelo numero indicado: \n>>");
					gets(comando);
					sprintf(query,"SELECT pergunta, resposta FROM questoes WHERE id_dominio = '%s';",comando);
					printf("============================================================================\n");
					listar();
				}else if(busca == 4){
					printf("VLW");
					printf("============================================================================\n");
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

