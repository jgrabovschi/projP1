#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesPortatil.h"


/********************************************************************************
Funcao lerDadosPortatil
Descricao: Lê dados de um portatil.
Aceita como parametros de entrada o vetor vPortateis e o inteiro quantPortateis.
Devolve "por return" a quantidade de portateis atualizada.
********************************************************************************/
int lerDadosPortatil(tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis){

    int posicao;
    if(quantPortateis == MAX_PORTATEIS){
        printf("\nErro! Impossivel acrescentar portateis(No maximo e possivel registar 30 portateis\n");
    }
    else{


        printf("\nNumero de indentificacao do portatil: ");
        vPortateis[quantPortateis].num = lerInteiro(1,MAX_NUM);
        posicao = procuraPortatil(vPortateis[quantPortateis].num, vPortateis, quantPortateis);
        if(posicao != -1){
            printf("Erro! Portatil ja existente. ");
        }
        else{
            printf("Designacao do computador(MAX. 30 caracteres): ");
            lerString(vPortateis[quantPortateis].designacao,MAX_DESIGNACAO);

            printf("Processador(i3 ou i5 ou i7): ");
            lerString(vPortateis[quantPortateis].processador, MAX_PROCESSADOR);
            if(strcmp(vPortateis[quantPortateis].processador,"i3")!=0 && strcmp(vPortateis[quantPortateis].processador,"i5")!=0 && strcmp(vPortateis[quantPortateis].processador,"i7")!=0){
                printf("Erro! Processador invalido.\n");
            }
            else{
                printf("RAM em GB(MAX. 64): ");
                vPortateis[quantPortateis].ram = lerInteiro(1,MAX_RAM);

                printf("Local onde se encontra o portatil(1-Residencias ou 2-Campus1 ou 3-Campus2 ou 4-Campus5): ");
                vPortateis[quantPortateis].local = lerInteiro(1,4);

                printf("Insira a data de aquisicao: \n");
                vPortateis[quantPortateis].dataAquisicao = lerData();

                printf("Valor do equipamento (em euro): ");
                vPortateis[quantPortateis].valor = lerFloat(0,MAX_VALOR);

                vPortateis[quantPortateis].estado = 1;

                vPortateis[quantPortateis].quantAvarias = 0;

                vPortateis[quantPortateis].quantRequisicoes = 0;

                vPortateis[quantPortateis].quantDiasRequisitado = 0;

                quantPortateis++;
            }
        }
    }

    return quantPortateis;
}


/********************************************************************************
Funcao mostrarPortateis
Descricao: Mostra os dados de todos os portateis ja registados.
Aceita como parametros de entrada o vetor vPortateis, o vetor dinamico vRequisicoes,
 o inteiro quantRequisicoes e o inteiro quantPortateis.
Não devolve nada (tipo void)
********************************************************************************/
void mostrarPortateis(tipoPortatil vPortatil[MAX_PORTATEIS],int quantPortateis,tipoRequisicao *vRequisicoes, int quantRequisicoes){
    int i;
    int j;

    if(quantPortateis==0){
        printf("\n\tNao existem portateis registados...\n");
    }
    else{
        printf("PORTATEIS REGISTADOS:\n");
        for(i=0;i<quantPortateis;i++){
            printf("\nPORTATIL NUMERO %d:\n", vPortatil[i].num);
            printf("\tDesignacao: %s\n", vPortatil[i].designacao);
            printf("\tProcessador: %s\n", vPortatil[i].processador);
            printf("\tMemoria RAM: %d GB\n", vPortatil[i].ram);
            printf("\tEstado: ");

            switch (vPortatil[i].estado){
            case 1:
                printf("Disponivel\n");
                break;
            case 2:
                printf("Requisitado\n");
                break;
            case 3:
                printf("Avariado\n");
                break;
            }
            printf("\tLocalizacao: ");
            switch (vPortatil[i].local){
            case 1:
                printf("Residencias\n");
                break;
            case 2:
                printf("Campus 1\n");
                break;
            case 3:
                printf("Campus 2\n");
                break;
            case 4:
                printf("Campus 5\n");
                break;
            }

            printf("\tData de aquisicao: %d - %d - %d\n", vPortatil[i].dataAquisicao.dia, vPortatil[i].dataAquisicao.mes, vPortatil[i].dataAquisicao.ano);
            printf("\tValor: %.2f\n", vPortatil[i].valor);
            printf("\tQuantidade de avarias: %d\n", vPortatil[i].quantAvarias);
            printf("\tQuantidade de requisicoes: %d\n", vPortatil[i].quantRequisicoes);
            printf("\tQuantidade de dias que esteve requisitado: %d\n", vPortatil[i].quantDiasRequisitado);
            if(vPortatil[i].quantRequisicoes){
                printf("\nInformacao das requisicoes do portatil %d: \n",vPortatil[i].num);
            }

            for(j=0;j<quantRequisicoes;j++){
                if(vRequisicoes[j].num == vPortatil[i].num){
                    mostraRequisicao(vRequisicoes[j]);
                }
            }
        }
    }
}



/********************************************************************************************************
Funcao procuraPortatil
Descricao: Procura a posicao de um portatil no vetor vPortateis a partir de um numero de identificacao.
Aceita como parametros de entrada um numero inteiro (identificao),o vetor vPortateis e o inteiro quantPortateis
Devolve "por return": -se for encontrado no vetor, a posicao do portatil(de 0 a 29);
                      -se não for encontrado, -1.
********************************************************************************************************/
int procuraPortatil (int numero,tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis){
    int i, posicao=-1;

    for (i=0; i<quantPortateis; i++){//percorre o vetor para encontrar um portatil com o numero na variavel "numero"
        if(numero==vPortateis[i].num){
            posicao = i;
            i = quantPortateis; //para sair do loop logo a seguir
        }
    }

    return posicao;
}

/********************************************************************************************************
Funcao contaPortateisDisponiveis
Descricao: Conta os Portateis que estão Disponiveis.
Aceita como parametros de entrada o vetor vPortateis e o inteiro quantPortateis
Devolve "por return" o numero de portateis diponiveis.
********************************************************************************************************/
int contaPortateisDisponiveis(tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis){

    int i;
    int conta=0; //variavel que conta o numero de portateis disponiveis

    for(i=0;i<quantPortateis;i++){ //percorre o vetor e conta os portateis que estao 1-disponiveis
        if(vPortateis[i].estado == 1){
            conta++;
        }
    }

    return conta;
}

/********************************************************************************
Funcao mudarLocalizacao
Descricao: Muda a localizacao de um portatil existente.
Aceita como parametros de entrada o vetor vPortateis e o inteiro quantPortateis.
********************************************************************************/
void mudarLocalizacao(tipoPortatil vPortateis[MAX_PORTATEIS],int quantPortateis){
    int pos, num, novoLocal;

    if(quantPortateis == 0){
        printf("\nImpossivel realizar operacao (Nao existem portateis)...\n");
    }
    else{
        printf("Indique o numero do portatil: ");
        num = lerInteiro(1,MAX_NUM);
        pos = procuraPortatil(num,vPortateis,quantPortateis);
        if(pos==-1 || vPortateis[pos].estado == 2){
            printf("Esse portatil nao existe ou o portatil escontra-se requisitado...\n");
        }
        else{
            printf("Indique a nova localizacao do portatil (1-Residencias; 2-Campus 1; 3-Campus 2; 4-Campus 5): ");
            novoLocal=lerInteiro(1,4);
            if(novoLocal==vPortateis[pos].local){
                printf("Este portatil ja se encontra nessa localizacao...\n");
            }
            else{
                vPortateis[pos].local=novoLocal;
                printf("Localizacao mudada com sucesso\n");
                printf("Nova localizacao: ");
                switch(novoLocal){
                    case 1:
                        printf("Residencias\n");
                        break;
                    case 2:
                        printf("Campus 1\n");
                        break;
                    case 3:
                        printf("Campus 2\n");
                        break;
                    default:
                        printf("Campus 5\n");
                }
            }
        }

    }
}

/********************************************************************************************************
Funcao guardaInfoPortateis
Descricao: Guarda a informacao sobre os Portateis num ficheiro binario.
Aceita como parametros o vetor vPortateis e o inteiro quantPortateis.
Não devolve nada(tipo void)
********************************************************************************************************/
void guardarInfoPortateis(tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis){

    FILE *ficheiro;
    int erro;

    ficheiro = fopen("InfoPortateis.dat","wb");

    if(ficheiro != NULL){

        fwrite(&quantPortateis,sizeof(int),1,ficheiro);
        fwrite(vPortateis,sizeof(tipoPortatil),quantPortateis,ficheiro);

        printf("Informacao guardada com sucesso!(informacao portateis)\n");

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheir(informacao portateis)o\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro(informacao portateis)...");
    }

}

/********************************************************************************************************
Funcao lerInfoPortateis
Descricao: Lê a informacao sobre os Portateis de um ficheiro binario.
Aceita como parametros o vetor vPortateis e o inteiro em *quantPortateis.
Não devolve nada(tipo void)
********************************************************************************************************/
void lerInfoPortateis(tipoPortatil vPortateis[MAX_PORTATEIS], int *quantPortateis){

    FILE *ficheiro;
    int erro;

    ficheiro = fopen("InfoPortateis.dat","rb");

    if(ficheiro != NULL){

        fread(&(*quantPortateis),sizeof(int),1,ficheiro);
        fread(vPortateis,sizeof(tipoPortatil),*quantPortateis,ficheiro);

        printf("Informacao lida com sucesso!(informacao portateis)\n");

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheiro(informacao portateis)\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro(informacao portateis)...");
    }

}
