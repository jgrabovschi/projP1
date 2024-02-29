#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesLeitura.h"
#include "funcoesPortatil.h"
#include "constantes.h"
#include "funcoesRequisicao.h"
#include "funcoesAvaria.h"


int menu(tipoPortatil vPortateis[MAX_PORTATEIS],int quantPortateis, tipoRequisicao *vRequisicoes, int quantRequisicoes);
int submenuRequisicoes();
int submenuAvarias();
int submenuPortateis();
void mostrarDadosEstatisticos(tipoPortatil vPortateis[MAX_PORTATEIS], tipoRequisicao *vRequisicoes, int quantPortateis, int quantRequisicoes);


/********************************************************************************************************
Funcao main
Descricao: É a função que permite "navegar" pelo menu e pelos diferentes submenus.
É aqui que são declarados os vetores de estruturas e as respetivas variaveis que os acompanham.
********************************************************************************************************/
int main()
{
    int opcao; //opcao do menu
    int opcaoReq; //opcao do submenu de requisicoes
    int opcaoPort; //opcao do submenu de portateis
    int opcaoAvar; //opcao do submenu de avarias
    tipoPortatil vPortateis[MAX_PORTATEIS]; // vetor de estruturas que guardam informacoes relevantes aos portateis
    int quantPortateis = 0; // variavel que acompanha o vetor anterior
    tipoRequisicao *vRequisicoes; // vetor de estruturas que guardam informacoes relevantes as reservas
    int quantRequisicoes = 0; // variavel que acompanha o vetor anterior
    tipoAvaria *vAvarias; // vetor de estruturas que guardam informacoes relevantes as avarias
    int quantAvarias = 0; // variavel que acompanha o vetor anterior

    vRequisicoes = NULL;
    vAvarias = NULL;

    do{
        opcao = menu(vPortateis, quantPortateis, vRequisicoes, quantRequisicoes);
        switch(opcao){
        case 1:
            opcaoPort = submenuPortateis();
            switch(opcaoPort){

                case 1:
                    quantPortateis = lerDadosPortatil(vPortateis,quantPortateis);
                    break;

                case 2:
                    mostrarPortateis(vPortateis,quantPortateis,vRequisicoes,quantRequisicoes);
                    break;

                case 3:
                    mudarLocalizacao(vPortateis,quantPortateis);

            }
            break;

        case 2:
            opcaoReq = submenuRequisicoes();
            switch(opcaoReq){
                case 1:
                    vRequisicoes = registarRequisicao(vPortateis,vRequisicoes, quantPortateis, &quantRequisicoes, vAvarias,quantAvarias);
                    break;

                case 2:
                    devolverPortatil(vRequisicoes,quantRequisicoes,vPortateis,quantPortateis);
                    break;

                case 3:
                    mostrarRequisicoes(vRequisicoes,quantRequisicoes);
                    break;

                case 4:
                    mostrarUmaRequisicao(vRequisicoes,quantRequisicoes);
                    break;

                case 5:
                    renovarRequisicao(vRequisicoes,quantRequisicoes);

            }
            break;

        case 3:
            opcaoAvar = submenuAvarias();
            switch(opcaoAvar){

                case 1:
                    vAvarias = registarAvaria(vPortateis,quantPortateis,vAvarias,&quantAvarias,vRequisicoes,quantRequisicoes);
                    break;

                case 2:
                    registarReparacao(vAvarias,quantAvarias, vPortateis, quantPortateis);
                    break;

                case 3:
                    mostraAvaria(vAvarias, quantAvarias);
            }
            break;

        case 4:
            guardarInfoPortateis(vPortateis,quantPortateis);
            guardarInfoRequisicoes(vRequisicoes,quantRequisicoes);
            guardarInfoAvarias(vAvarias,quantAvarias);
            break;

        case 5:
            lerInfoPortateis(vPortateis,&quantPortateis);
            vRequisicoes = lerInfoRequisicoes(vRequisicoes,&quantRequisicoes);
            vAvarias = lerInfoAvarias(vAvarias,&quantAvarias);
            break;

        case 6:
            mostrarDadosEstatisticos(vPortateis,vRequisicoes,quantPortateis,quantRequisicoes);
            break;

        default:
            printf("\nA sair do programa... \n");
        }
    }while(opcao != MAX_OPCAO);

    free(vRequisicoes);
    free(vAvarias);
    return 0;
}

/********************************************************************************************************
Funcao menu
Descricao: Mostra o menu de opcoes que permite "navegar" pelo programa
Aceita como parametros o vetor vPortateis, o inteiro quantPortateis, o vetor vRequisicoes e o inteiro quantRequisicoes.
Devolve por return a opcao selecionada.
********************************************************************************************************/
int menu(tipoPortatil vPortateis[MAX_PORTATEIS],int quantPortateis, tipoRequisicao *vRequisicoes, int quantRequisicoes){

    int opcao;
    int portateisDisponiveis = 0;
    int requisicoesAtivas = 0;

    portateisDisponiveis = contaPortateisDisponiveis(vPortateis, quantPortateis);
    requisicoesAtivas = contaRequisicoesAtivas(vRequisicoes, quantRequisicoes);


    printf("\n******************************************************************************\n");
    printf("\t\tGestao da requisicao de computadores portateis\n\n");
    printf("Quantidade de portateis existentes: %d\n", quantPortateis);
    printf("Quantidade de portateis disponiveis: %d\n", portateisDisponiveis);
    printf("Quantidade total de requisicoes efetuadas: %d\n", quantRequisicoes);
    printf("Quantidade total de requisicoes ativas: %d\n\n", requisicoesAtivas);
    printf("Escolha uma opcao:\n");
    printf("1- Portateis\n");
    printf("2- Requisicoes\n");
    printf("3- Avarias\n");
    printf("4- Guardar informacao em ficheiros binarios\n");
    printf("5- Ler informacao de ficheiros binarios\n");
    printf("6- Dados estatisticos\n");
    printf("7- Sair do Programa\n\n");
    printf("\tOpcao-> ");
    opcao = lerInteiro(MIN_OPCAO,MAX_OPCAO);
    printf("\n******************************************************************************\n");

    return opcao;
}


/********************************************************************************************************
Funcao submenuRequisicoes
Descricao: Mostra o menu de opcoes que permite "navegar" pelo submenu das requisicoes
Não tem parametros de entrada
Devolve por return a opcao selecionada.
********************************************************************************************************/
int submenuRequisicoes(){

    int opcao;

    printf("\n******************************************************************************\n");
    printf("\t\tSubmenu Requisicoes\n");
    printf("1- Fazer Requisicao de um portatil\n");
    printf("2- Devolver Portatil\n");
    printf("3- Mostrar Requisicoes\n");
    printf("4- Mostrar uma unica requisicao\n");
    printf("5- Renovar Requisicoes\n");
    printf("6- Voltar\n\n");
    printf("\tOpcao-> ");
    opcao = lerInteiro(MIN_OPCAO,MAX_OPCAOREQ);
    printf("\n******************************************************************************\n");


    return opcao;
}

/********************************************************************************************************
Funcao submenuAvarias
Descricao: Mostra o menu de opcoes que permite "navegar" pelo submenu das avarias
Não tem parametros de entrada
Devolve por return a opcao selecionada.
********************************************************************************************************/
int submenuAvarias(){

    int opcao;

    printf("\n******************************************************************************\n");
    printf("\t\tSubmenu Avarias\n");
    printf("1- Registar Avaria\n");
    printf("2- Registar Reparacao\n");
    printf("3- Mostrar Avarias\n");
    printf("4- Voltar\n\n");
    printf("\tOpcao-> ");
    opcao = lerInteiro(MIN_OPCAO,MAX_OPCAOAVAR);
    printf("\n******************************************************************************\n");

    return opcao;
}

/********************************************************************************************************
Funcao submenuRequisicoes
Descricao: Mostra o menu de opcoes que permite "navegar" pelo submenu das requisicoes
Não tem parametros de entrada
Devolve por return a opcao selecionada.
********************************************************************************************************/
int submenuPortateis(){

    int opcao;

    printf("\n******************************************************************************\n");
    printf("\t\tSubmenu Portateis\n");
    printf("1- Registar portatil\n");
    printf("2- Mostrar portateis\n");
    printf("3- Mudar localizacao de um portatil\n");
    printf("4- Voltar\n\n");
    printf("\tOpcao -> ");
    opcao = lerInteiro(MIN_OPCAO,MAX_OPCAOPORT);
    printf("\n******************************************************************************\n");

    return opcao;
}

/********************************************************************************************************
Funcao mostrarDadosEstatisticos
Descricao: Calcula, procura e mostra as estatisticas requeridas.
Aceita como parametro o vetor vPortateis, o vetor dinamico vRequisicoes, o inteiro quantPortateis
 e o inteiro quantRequisicoes.
********************************************************************************************************/
void mostrarDadosEstatisticos(tipoPortatil vPortateis[MAX_PORTATEIS], tipoRequisicao *vRequisicoes, int quantPortateis, int  quantRequisicoes){

    int i, processadorI3=0, processadorI5=0, processadorI7=0; // contadores para cada processador
    float percentI3 = 0.0, percentI5 = 0.0, percentI7 = 0.0, mediaMulta = 0; //percentagens de cada processador e media da multa
    int quantMultas=0, multaSoma=0; //variaveis para auxiliar o calculo da media da multa
    int tipoutente1=0, tipoutente2=0, tipoutente3=0; // contadores para cada tipo de utente
    int diasAux = 0;
    int diasRequisicao;

    for(i=0;i<quantPortateis;i++){
        if(strcmp(vPortateis[i].processador,"i3")==0){
            processadorI3++;
        }
        else{
            if(strcmp(vPortateis[i].processador,"i5")==0){
                processadorI5++;
            }
            else{
                processadorI7++;
            }
        }
    }
    if(quantPortateis!=0){
        percentI3 = ((float)processadorI3/quantPortateis)*100;
        percentI5 = ((float)processadorI5/quantPortateis)*100;
        percentI7 = ((float)processadorI7/quantPortateis)*100;
    }

    for(i=0;i<quantRequisicoes;i++){
        if(vRequisicoes[i].multa!=0){
            multaSoma += vRequisicoes[i].multa;
            quantMultas++;
        }

        switch(vRequisicoes[i].tipoUtente){
            case 1: tipoutente1++;
                    break;
            case 2: tipoutente2++;
                    break;
            default:tipoutente3++;
        }
    }

    if(quantMultas){
        mediaMulta = (float)multaSoma/quantMultas;
    }

    for(i=0;i<quantRequisicoes;i++){
        diasRequisicao = converteDataDias(vRequisicoes[i].dataDevolucao);
        if(diasRequisicao>diasAux){
           diasAux = diasRequisicao;
        }
    }
    printf("DADOS ESTATISTICOS:\n\n");
    printf("\t Percentagem de portateis com i3: %.2f%%\n", percentI3);
    printf("\t Percentagem de portateis com i5: %.2f%%\n", percentI5);
    printf("\t Percentagem de portateis com i7: %.2f%%\n", percentI7);
    printf("\t Media das multas pagas: %.2f\n", mediaMulta);
    printf("\t Tipo(s) de utente com menos requisicoes: ");
    if(tipoutente1==tipoutente2&&tipoutente2==tipoutente3){
        printf("Estudante, Docente, Tecnico administrativo (%d requisicoes)\n", tipoutente1);
    }
    else{
        if(tipoutente1==tipoutente2&&tipoutente1<tipoutente3){
            printf("Estudante, Docente (%d requisicoes)\n",tipoutente1);
        }
        else{
            if(tipoutente1==tipoutente3&&tipoutente1<tipoutente2){
                printf("Estudante, Tecnico administrativo (%d requisicoes)\n", tipoutente1);
            }
            else{
                if(tipoutente2==tipoutente3&&tipoutente2<tipoutente1){
                    printf("Docente, Tecnico administrativo (%d requisicoes)\n",tipoutente2);
                }
                else{
                    if(tipoutente1<tipoutente2&&tipoutente1<tipoutente3){
                        printf("Estudante (%d requisicoes)\n", tipoutente1);
                    }
                    else{
                        if(tipoutente2<tipoutente1&&tipoutente2<tipoutente3){
                        printf("Docente (%d requisicoes)\n", tipoutente2);
                        }
                        else{
                            printf("Tecnico administrativo (%d requisicoes)\n", tipoutente3);
                        }
                    }
                }
            }
        }
    }
    printf("\t Ultima(s) devolucao(oes): \n");
    for(i=0;i<quantRequisicoes;i++){
        diasRequisicao = converteDataDias(vRequisicoes[i].dataDevolucao);
        if(diasRequisicao == diasAux){
            printf("\n\t\tCodigo da requisicao: %s\n", vRequisicoes[i].codigo);
            printf("\t\tNumero de identificacao do portatil: %d\n", vRequisicoes[i].num);
            printf("\t\tNome do utente: %s\n", vRequisicoes[i].nomeUtente);
        }
    }
}
