#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesAvaria.h"


/********************************************************************************************************
Funcao *registarAvaria
Descricao: Regista uma avaria.
Aceita como parametros de entrada um vetor vPortateis,o vetor dinamico vAvarias, o vetor dinamico vRequisicoes
 o inteiro quantPortateis, o inteiro quantRequisicoes e o inteiro em *quantAvarias.
Devolve "por return": o vetor dinamico vAvarias.
********************************************************************************************************/
tipoAvaria *registarAvaria(tipoPortatil *vPortateis, int quantPortateis, tipoAvaria *vAvarias, int *quantAvarias, tipoRequisicao *vRequisicoes, int quantRequisicoes){
    int pos, codigo;
    int diasAvaria;
    int diasAquisicao;
    int diasDev;
    int diasAvariaAnt;
    tipoAvaria *v;
    tipoData dataAntDev;
    tipoData dataAntAvar;

    v = vAvarias;

    if(quantPortateis==0){
        printf("Nao existem portateis disponiveis...\n");
    }
    else{
        printf("Introduza o numero de identificacao do portatil: ");
        codigo=lerInteiro(1,9999);
        pos=procuraPortatil(codigo,vPortateis,quantPortateis);
        if(pos==-1){
            printf("Nao existe nenhum portatil registado com esse numero...\n");
        }
        else{
            if(vPortateis[pos].estado == 2){
                printf("Nao e possivel registar uma avaria num portatil requisitado...\nO portatil deve ser devolvido imediatamente!\n");
            }
            else{
                vAvarias = realloc(vAvarias,((*quantAvarias)+1)*sizeof(tipoAvaria));

                if(vAvarias == NULL){
                    printf("Erro ao realocar memoria...\n");
                    vAvarias = v;
                }
                else{
                    printf("Qual o tipo da avaria?(1-temporaria , 2-permanente): ");
                    vAvarias[*quantAvarias].tipo = lerInteiro(1,2);
                    diasAquisicao = converteDataDias(vPortateis[pos].dataAquisicao);
                    dataAntDev = procuraDataDevolucaoAnterior(vRequisicoes,quantRequisicoes,vAvarias[*quantAvarias].num);
                    diasDev = converteDataDias(dataAntDev);
                    dataAntAvar = procuraDataAvariaAnterior(vAvarias,*quantAvarias,vAvarias[*quantAvarias].num);
                    diasAvariaAnt = converteDataDias(dataAntAvar);
                    do{
                        printf("Data da avaria:\n");
                        vAvarias[*quantAvarias].data = lerData();
                        diasAvaria = converteDataDias(vAvarias[*quantAvarias].data);
                        if(!(diasAvaria>diasAquisicao&&diasAvaria>diasDev&&diasAvaria>diasAvariaAnt)){
                            printf("Data Invalida!\n");
                        }
                    }while(!(diasAvaria>diasAquisicao&&diasAvaria>diasDev&&diasAvaria>diasAvariaAnt));

                    vAvarias[*quantAvarias].duracao = 0;

                    vAvarias[*quantAvarias].num = vPortateis[pos].num;

                    if(vPortateis[pos].estado == 1){
                        printf("O portatil numero %d encontra-se agora registado como avariado\n",vPortateis[pos].num);
                    }
                    else{
                        printf("Avaria adicionada\n");
                    }
                    vPortateis[pos].estado=3;
                    vPortateis[pos].quantAvarias++;

                    (*quantAvarias)++;
                }
            }
        }
    }
    return vAvarias;
}


/********************************************************************************************************
Funcao registarReparacao
Descricao: Regista a reparacao de um portatil com avaria temporaria.
Aceita como parametros o vetor vAvarias, o inteiro quantAvarias, o vetor vPortateis, e o inteiro quantPortateis.
Não devolve nenhum dado (tipo void)
********************************************************************************************************/
void registarReparacao(tipoAvaria *vAvarias, int quantAvarias, tipoPortatil *vPortateis, int quantPortateis){
    int posPort, posAvar, codigo;

    if(quantAvarias==0){
        printf("Nao existem portateis avariados...\n");
    }
    else{
        printf("Introduza o numero de identificacao do portatil: ");
        codigo=lerInteiro(1,9999);
        posPort=procuraPortatil(codigo,vPortateis,quantPortateis);
        if(posPort==-1){
            printf("Nao existe nenhum portatil registado com esse numero...\n");
        }
        else{
            switch(vPortateis[posPort].estado){
                case 3:

                    posAvar = procuraAvaria(codigo,vAvarias,quantAvarias);

                    if(vAvarias[posAvar].tipo == 1){

                        posAvar = procuraAvaria(codigo,vAvarias,quantAvarias);
                        if(!(posAvar!=-1 && vAvarias[posAvar].duracao != 0)){
                            vPortateis[posPort].estado=1;
                            printf("O portatil numero %d encontra-se agora consertado e disponivel\n",vPortateis[posPort].num);
                        }
                        else{
                            printf("1 Avaria resolvida!\n");
                        }


                        printf("Duracao da avaria em dias: ");
                        vAvarias[posAvar].duracao = lerInteiro(1,MAX_NUM);
                    }
                    else{
                        printf("O portatil esta avariado permanentemente...\n");
                    }

                    break;
                case 2:
                    printf("Nao e possivel registar um concerto num portatil requisitado...\n");
                    break;
                default:
                    printf("Esse portatil nao se encontra avariado de momento...\n");
            }
        }
    }
}


/********************************************************************************************************
Funcao procuraAvaria
Descricao: Procura a posicao de uma avaria no vetor vAvarias a partir de um numero de identificacao.
Aceita como parametros de entrada um numero inteiro (identificao),o vetor vAvarias e o inteiro quantAvarias
Devolve "por return": -se for encontrado no vetor, a posicao da avaria no vetor;
                      -se não for encontrado, -1.
********************************************************************************************************/
int procuraAvaria (int numero,tipoAvaria *vAvarias, int quantAvarias){
    int i, posicao=-1;

    for (i=0; i<quantAvarias; i++){//percorre o vetor para encontrar uma avaria nao resolvida com o numero na variavel "numero"
        if(numero==vAvarias[i].num && vAvarias[i].duracao == 0){
            posicao = i;
            i = quantAvarias; //para sair do loop logo a seguir
        }
    }

    return posicao;
}

/********************************************************************************************************
Funcao mostrarAvarias
Descricao: Mostra os detalhes de todas as avarias.
Aceita como parametros o vetor vAvarias e o inteiro quantAvarias.
Não devolve nenhum dado (tipo void)
********************************************************************************************************/
void mostraAvaria(tipoAvaria *vAvarias, int quantAvarias){

    int i;

    if(quantAvarias == 0){
        printf("\nNao existem avarias para mostrar...\n");
    }
    else{
        for(i=0; i<quantAvarias; i++){
            printf("\nAVARIA DO PORTATIL %d:\n", vAvarias[i].num);
            printf("\tData da avaria: %d - %d - %d\n", vAvarias[i].data.dia, vAvarias[i].data.mes, vAvarias[i].data.ano);
            printf("\tTipo: ");
            if(vAvarias[i].tipo == 1){
                printf("Temporaria\n");
                if(vAvarias[i].duracao == 0){
                    printf("\tEstado: Por reparar...\n");
                }
                else{
                    printf("\tEstado: Reparado\n\tDuracao: %d dias", vAvarias[i].duracao);
                }
            }
            else{
                printf("Permanente\n");
            }
        }
    }
}

/********************************************************************************************************
Funcao procuraDataAvariaAnterior
Descricao: Procura a data da ultima avaria que aconteceu num portatil no vetor vAvarias.
Aceita como parametros o vetor vAvarias, o inteiro quantAvarias e o inteiro num (numero do portatil).
Devolve a data da ultima avaria que aconteceu num portatil.
********************************************************************************************************/
tipoData procuraDataAvariaAnterior(tipoAvaria *vAvarias, int quantAvarias, int num){

    int i;
    tipoData dataAnterior;
    dataAnterior.ano = 0;
    dataAnterior.mes = 0;
    dataAnterior.dia = 0;

    for(i=0; i<quantAvarias; i++){
        if((vAvarias[i].num == num) && (vAvarias[i].duracao != 0)){
            dataAnterior.dia = vAvarias[i].data.dia;
            dataAnterior.mes = vAvarias[i].data.mes;
            dataAnterior.ano = vAvarias[i].data.ano;
        }
    }

    return dataAnterior;
}

/********************************************************************************************************
Funcao guardaInfoAvarias
Descricao: Guarda a informacao sobre as avarias num ficheiro binario.
Aceita como parametros o vetor vAvarias e o inteiro quantAvarias.
Não devolve nada(tipo void)
********************************************************************************************************/
void guardarInfoAvarias(tipoAvaria *vAvarias,int quantAvarias){

    FILE *ficheiro;
    int erro;

    ficheiro = fopen("InfoAvarias.dat","wb");

    if(ficheiro != NULL){

        fwrite(&quantAvarias,sizeof(int),1,ficheiro);
        fwrite(vAvarias,sizeof(tipoAvaria),quantAvarias,ficheiro);

        printf("Informacao guardada com sucesso(informacao avarias)!\n");

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheiro(informacao avarias)\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro(informacao avarias)...");
    }

}

/********************************************************************************************************
Funcao *lerInfoAvarias
Descricao: Lê a informacao sobre as avarias de um ficheiro binario.
Aceita como parametros de entrada o vetor dinamico vAvarias e o inteiro em *quantAvarias.
Devolve "por return": o vetor dinamico.
********************************************************************************************************/
tipoAvaria *lerInfoAvarias(tipoAvaria *vAvarias, int *quantAvarias){

    FILE *ficheiro;
    int erro;
    tipoAvaria *v;
        /*backup do vetor dinamico*/
    v = vAvarias;

    ficheiro = fopen("InfoAvarias.dat","rb");

    if(ficheiro != NULL){

        fread(&(*quantAvarias),sizeof(int),1,ficheiro);

        vAvarias = realloc(vAvarias,(*quantAvarias)*sizeof(tipoAvaria));

        if(vAvarias == NULL && *quantAvarias != 0){
            printf("Erro ao alocar memoria(informacao avarias)...");
            vAvarias = v;
        }
        else{
            fread(vAvarias,sizeof(tipoAvaria),*quantAvarias,ficheiro);

            printf("Informacao lida com sucesso!(informacao avarias)\n");
        }

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheiro(informacao avarias)\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro(ficheiro inexistente)(informacao avarias)...");
    }

    return vAvarias;
}
