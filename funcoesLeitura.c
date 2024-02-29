#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "funcoesLeitura.h"


/********************************************************************************************************
Funcao lerInteiro
Descricao: Lê e coloca a data numa estrutura do tipo tipoData.
Devolve a estrutura do tipo tipoData.
********************************************************************************************************/
int lerInteiro(int min, int max){
    int numero, controlo;

    do{// Repete leitura enquanto valor introduzido não for numérico, e não estiver no intervalo desejado [min , max]

        controlo = scanf("%d", &numero);// scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin();/* elimina caracteres que ficaram no buffer stdin */
        if(numero<min || numero>max || controlo==0){
            printf("Erro! Numero Invalido. Insira novamente: ");
        }

    }while (numero<min || numero>max || controlo==0);

    return numero;

}


/********************************************************************************************************
Funcao lerFloat
Descricao: Lê um numero de virgula flutuante entre "min" e "max".
Devolve o numero de virgula flutuante que foi lido.
********************************************************************************************************/
float lerFloat(float min, float max){
    float numero;
    int controlo;

    do{// Repete leitura enquanto valor introduzido não for numérico, e não estiver no intervalo desejado (min -> max)

        controlo = scanf("%f", &numero);// scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin();/* elimina caracteres que ficaram no buffer stdin */
        if(numero<min || numero>max || controlo==0){
            printf("Erro! Numero Invalido. Insira novamente: ");
        }
    }while (numero<min || numero>max || controlo==0);

    return numero;
}


/********************************************************************************************************
Funcao lerString
Descricao: Lê uma string, com um maáximo de "max" caracteres, introduzida pelo utilizador e coloca-a num vetor de caracteres
********************************************************************************************************/
void lerString(char vetor[], int max){
    int tamanhoString;

    do{/*Repete leitura caso sejam introduzidas strings apenas com o \n (tamanhoString == 1) */
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }while(tamanhoString == 1);

    if (vetor[tamanhoString-1] != '\n'){/* armazenados no vetor todos os caracteres */
        limpaBufferStdin();/* elimina caracteres que ficaram no buffer stdin */
    }
    else{
        vetor[tamanhoString-1] ='\0';/*substitui \n da string armazenada em vetor por \0 */
    }
}

/********************************************************************************************************
Funcao limpaBufferStdin
Descricao: Elimina "lixo" contido em stdin.
********************************************************************************************************/
void limpaBufferStdin (void){
    char lixo;

    do{
        lixo=getchar();
    }while (lixo!='\n' && lixo!=EOF);
}

/********************************************************************************************************
Funcao lerData
Descricao: Lê e coloca a data numa estrutura do tipo tipoData.
Devolve a estrutura do tipo tipoData.
********************************************************************************************************/
tipoData lerData(){
    tipoData data;

    printf("Ano: ");
    data.ano = lerInteiro(MENOR_ANO, MAIOR_ANO);
    printf("Mes: ");
    data.mes = lerInteiro(1, 12);

    printf("Dia: ");
        switch (data.mes){
        case 2: // fevereiro
           if ((data.ano%400==0) || (data.ano%4==0 && data.ano%100!=0)){
                data.dia = lerInteiro(1, 29);
           }
           else{
                data.dia = lerInteiro(1, 28);
           }
           break;
        case 4: /*meses com 30 dias*/
        case 6:
        case 9:
        case 11:
            data.dia = lerInteiro(1, 30);
            break;
        default: // meses com 31 dias
            data.dia = lerInteiro(1, 31);
    }

    return data;
}

/********************************************************************************************************
Funcao maxDiasMes
Descricao: Dependendo do mês e do ano devolve a quantidade de dias que esse mês tem
********************************************************************************************************/
int maxDiasMes(int mes, int ano){

    int maxdias;

    switch (mes){
                case 2:// fevereiro
                    if ((ano%400==0) || (ano%4==0 && ano%100!=0)){
                        maxdias = 29;
                    }
                    else{
                        maxdias = 28;
                    }
                    break;
                case 4:   /*meses com 30 dias*/
                case 6:
                case 9:
                case 11:
                    maxdias = 30;
                    break;
                default: // meses com 31 dias
                    maxdias = 31;
            }

    return maxdias;
}

/********************************************************************************************************
Funcao converteDataDias
Descricao: Converte uma data num numero de dias relativamente a 01/01/2014(MENOR_ANO).
Aceita como parametro uma estrutura do tipo tipoData.
Devolve o inteiro com esse numero de dias.
********************************************************************************************************/
int converteDataDias(tipoData data){

    int totalDias, i;
    totalDias = 0;

    totalDias = (data.ano - MENOR_ANO) * 365;

    for (i=MENOR_ANO; i<data.ano; i++){
        if((i%400==0) || (i%4==0 && i%100!=0)){
            totalDias++; /* Ano bissexto */
        }
    }

    for (i=1; i<data.mes; i++){ //soma dos dias de janeiro ao mes em causa
        totalDias += maxDiasMes(i,data.ano);
    }

    totalDias +=  data.dia; //soma os restantes dias

    return totalDias;

}
