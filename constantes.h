#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define MAX_PORTATEIS 30
#define MIN_OPCAO 1
#define MAX_OPCAO 7
#define MAX_NUM 9999
#define MAX_DESIGNACAO 30
#define MAX_PROCESSADOR 3
#define MAX_RAM 64
#define MENOR_ANO 2014
#define MAIOR_ANO 2023
#define MAX_VALOR 9999.0
#define MAX_CODIGOREQ 10
#define MAX_NOME 80
#define MAX_PRAZO 30
#define MAX_OPCAOREQ 6
#define MAX_OPCAOAVAR 4
#define MAX_OPCAOPORT 4

typedef struct{
    int dia;
    int mes;
    int ano;
}tipoData;

typedef struct{
    int num; //numero de indetificacao
    char designacao[MAX_DESIGNACAO]; // modelo do portatil
    char processador[MAX_PROCESSADOR]; // processador (i3,i5,i7)
    int ram; // no maximo 64gb
    int estado; //1=disponivel; 2=requisitado; 3=avariado
    int local; //1=Residências; 2=Campus1; 3=Campus2; 4=Campus5
    tipoData dataAquisicao; //data da aquisicao do computador
    float valor; //preço do portátil
    int quantRequisicoes;
    int quantAvarias;
    int quantDiasRequisitado; // total de dias que o portatil esteve requisitado
}tipoPortatil;

typedef struct{
    char codigo[MAX_CODIGOREQ];
    int num;
    char nomeUtente[MAX_NOME];
    int tipoUtente; //1-Estudante; 2-Docente; 3-Tecnico administrativo
    tipoData dataRequisicao;
    int prazo; // prazo da devolucao
    int estadoRequisicao; //1-ativa; 2=concluida
    tipoData dataDevolucao;
    int localDevolucao; //1=Residências; 2=Campus1; 3=Campus2; 4=Campus5
    int multa;
    int duracao; //duracao da requisicao
}tipoRequisicao;

typedef struct{

    int num; // numero do portatil avariado
    int tipo; // 1-temporaria; 2- permanente
    tipoData data; // data da avaria
    int duracao; // duracao da avaria em dias

}tipoAvaria;

#endif // CONSTANTES_H_INCLUDED
