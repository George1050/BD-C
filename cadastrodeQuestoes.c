#include<stdio.h>
#include<string.h>
#include "libpq-fe.h"
#include "chamadas.h"

/*Objeto de conexão*/
PGconn *conn = NULL;
int		nFields;
int     i,j;

/*Ponteiro de resultado*/
PGresult *res;
/*realiza a conexão*/
int conexao(){

	conn = PQconnectdb("host=127.0.0.1 dbname=BD_CADQUEST user=postgres password=12031997");
	
	if(PQstatus(conn) == CONNECTION_OK)
	{
	    printf("Conexão com o BD efetuada com sucesso. \n\n");
	}
	else
	{
	    printf("Falha na conexão. Erro: %s", PQerrorMessage(conn));
	    PQfinish(conn);
	    return -1;
	}
	
	/*Verifica se a conexão está aberta e a encerra*/
	if(conn != NULL)
	    PQfinish(conn);
}
    
struct cadastroQuestoes{
	int id;
	char dominio[100];
	char tema[100];
	int dificuldade;
	char pergunta[400];
	char reposta[400];
}cad;

void cadastro(){
//	printf("Informe o identificador: ");
//	scanf("%d",&cad.id);
//	setbuf(stdin, NULL);
//	printf("Informe o Dominio da Questão: ");
//	gets(cad.dominio);
//	printf("Informe o Tema da Questao: ");
//	gets(cad.tema);
//	printf("Escolha a Dificuldade: \n 1.Facil 2.Medio 3.Dificil\n>>");
//	scanf("%d",&cad.dificuldade);
//	setbuf(stdin, NULL);
//	printf("============================================================================\n"
//			"Escreva a Pergunta: \n>>");
//	gets(cad.pergunta);
//	printf("============================================================================\n");
//	printf("Escreva a Resposta: \n>>");
//	gets(cad.reposta);
//	printf("Obrigado pela sua atenção\n");
	
	/*Executa o comando*/
    /*Aqui você substitui a query por outras. Colocamos apenas uma como exemplo.*/
    tema(res);
    res = PQexec(conn,res);
    	
        switch(PQresultStatus(res)){
            case PGRES_EMPTY_QUERY:
                printf("Nada aconteceu. ");
                break;
            case PGRES_FATAL_ERROR:
                printf("Error in query: %s ", PQresultErrorMessage(res));
                break;
            case PGRES_COMMAND_OK:
                printf("%s linhas afetadas. ", PQcmdTuples(res));
                break;
            default:
                printf("Algum outro resultado ocorreu. ");
                break;
        }
        /*Libera o nosso objeto*/
        PQclear(res);
    /*Verifica se a conexão está aberta e a encerra*/
	if(conn != NULL)
		PQfinish(conn);
}
void listar(){

}void buscar(){
	printf("VLW!!!");
}

int main(){
	conexao();
    //MENU
	printf("===================== Biblioteca de Questoes =====================\n");
	
	int opcao;
	
	do{
		printf("\tDeseja 1.Cadastrar 2.Buscar 3.Listar 4.Sair");
		scanf("%d", &opcao);
		setbuf(stdin, NULL);
		switch(opcao){
			case 1:
				cadastro();
				break;
			case 2:
				buscar();
				break;
			case 3:
				listar();
				break;
			default:
				printf("Opcao invalida!!!");
		}
	}while(opcao != 4);
	
	return 0;
}

