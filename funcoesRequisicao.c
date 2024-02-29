#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "funcoesRequisicao.h"

/********************************************************************************************************
Funcao *registarRequisicao
Descricao: Registar uma requisicao.
Aceita como parametros de entrada um vetor vPortateis,o vetor dinamico vRequisicoes, o vetor dinamico vAvarias
 o inteiro quantPortateis, o inteiro em *quantRequisicoes e o inteiro quantAvarias.
Devolve "por return": o vetor dinamico vRequisicoes.
********************************************************************************************************/
tipoRequisicao *registarRequisicao(tipoPortatil vPortateis[MAX_PORTATEIS], tipoRequisicao *vRequisicoes, int quantPortateis, int *quantRequisicoes, tipoAvaria *vAvarias, int quantAvarias){
    int posPortatil, posRequisicao;
    tipoRequisicao *v; //vetor de backup
    int portateisDisponiveis;
    tipoData dataAntAvaria;
    tipoData dataAntDev;
    int diasRequisicao;
    int diasAquisicao;
    int diasAvaria;
    int diasDevolucao;

    v = vRequisicoes;

    portateisDisponiveis = contaPortateisDisponiveis(vPortateis, quantPortateis);

    if(portateisDisponiveis==0){
        printf("Nao existem portateis disponiveis para requisitar...\n");
    }
    else{
        vRequisicoes = realloc(vRequisicoes,((*quantRequisicoes)+1)*sizeof(tipoRequisicao));
        if(vRequisicoes==NULL){
            printf("Memoria insuficiente...\n");
            vRequisicoes = v;
        }
        else{

            printf("Insira o codigo da requisicao: ");
            lerString(vRequisicoes[*quantRequisicoes].codigo,MAX_CODIGOREQ);
            posRequisicao = procuraRequisicao(vRequisicoes[*quantRequisicoes].codigo,vRequisicoes, *quantRequisicoes);
            if(posRequisicao!=-1){
                printf("Codigo ja existente. ");
            }
            else{

                    printf("Insira o numero do portatil requisitado: ");
                    vRequisicoes[*quantRequisicoes].num = lerInteiro(0,MAX_NUM);
                    posPortatil=procuraPortatil(vRequisicoes[*quantRequisicoes].num, vPortateis, quantPortateis);
                    if(posPortatil==-1){
                        printf("O portatil com esse numero nao esta registado...\n");
                    }
                    else{
                        switch(vPortateis[posPortatil].estado){ //
                            case 2: printf("O portatil ja se encontra requisitado...\n");
                                    break;
                            case 3: printf("O portatil encontra-se avariado...\n");
                                    break;
                            default:printf("Insira o nome do utente a fazer a requisicao: ");
                                    lerString(vRequisicoes[*quantRequisicoes].nomeUtente,MAX_NOME);

                                    printf("Indique o tipo de utente (1-estudante ou 2-docente ou 3-tecnico administrativo): ");
                                    vRequisicoes[*quantRequisicoes].tipoUtente=lerInteiro(1,3);

                                    dataAntDev = procuraDataDevolucaoAnterior(vRequisicoes,*quantRequisicoes,vRequisicoes[*quantRequisicoes].num);
                                    diasDevolucao = converteDataDias(dataAntDev);
                                    diasAquisicao = converteDataDias(vPortateis[posPortatil].dataAquisicao);
                                    dataAntAvaria = procuraDataAvariaAnterior(vAvarias,quantAvarias,vPortateis[posPortatil].num);
                                    diasAvaria = converteDataDias(dataAntAvaria);

                                    do{
                                        printf("Insira a data de requisicao:\n");
                                        vRequisicoes[*quantRequisicoes].dataRequisicao=lerData();
                                        diasRequisicao = converteDataDias(vRequisicoes[*quantRequisicoes].dataRequisicao);

                                        if(!(diasRequisicao>diasAquisicao && diasRequisicao>diasAvaria && diasRequisicao>diasDevolucao)){
                                                printf("Data invalida! Data anterior a data de aquisicao ou a data de devolucao anterior...\n");
                                        }

                                    }while(!(diasRequisicao>diasAquisicao && diasRequisicao>diasAvaria && diasRequisicao>diasDevolucao));

                                    printf("Insira o prazo (dias): ");
                                    vRequisicoes[*quantRequisicoes].prazo=lerInteiro(1,MAX_PRAZO);

                                    vPortateis[posPortatil].estado=2; //muda para requisitado
                                    vPortateis[posPortatil].quantRequisicoes++; // incrementa o numero de requisicoes
                                    vRequisicoes[*quantRequisicoes].estadoRequisicao = 1; //ativo
                                    vRequisicoes[*quantRequisicoes].duracao = 0; // inicializa a duracao a 0
                                    vRequisicoes[*quantRequisicoes].multa = 0; // inicializa a multa a 0
                                    vRequisicoes[*quantRequisicoes].dataDevolucao.dia = 0;
                                    vRequisicoes[*quantRequisicoes].dataDevolucao.mes = 0;
                                    vRequisicoes[*quantRequisicoes].dataDevolucao.ano = 0;

                                    (*quantRequisicoes)++;
                        }
                    }
            }

        }
    }
    return vRequisicoes;
}


/********************************************************************************************************
Funcao procuraRequisicao
Descricao: Procura a posicao de uma requisicao no vetor vRequisicoes a partir de um codigo.
Aceita como parametros de entrada um codigo,o vetor vRequisicoes e o inteiro quantRequisicoes
Devolve "por return": -se for encontrado no vetor, a posicao da requisicao no vetor
                      -se não for encontrado, -1.
********************************************************************************************************/
int procuraRequisicao (char codigo[MAX_CODIGOREQ],tipoRequisicao *vRequisicoes, int quantRequisicoes){
    int i, posicao=-1;

    for (i=0; i<quantRequisicoes; i++){//percorre o vetor para encontrar uma requisicao com o numero na variavel "numero"
        if(strcmp(vRequisicoes[i].codigo,codigo)==0){
            posicao = i;
            i = quantRequisicoes; //para sair do loop logo a seguir
        }
    }

    return posicao;
}


/********************************************************************************************************
Funcao devolverPortatil
Descricao: Atualiza os dados do vetor de requisicoes para registar uma devolucao.
Aceita como parametros o vetor vRequisicoes, inteiro quantRequisicoes, o vetor vPortateis e o inteiro quantPortateis.
Não devolve nenhum dado (tipo void)
********************************************************************************************************/
void devolverPortatil(tipoRequisicao *vRequisicoes, int quantRequisicoes, tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis){

    int posReq;
    int posPort;
    int diasDevolucao;
    int diasRequisicao;
    char codigo[MAX_CODIGOREQ]; // codigo do portatil a devolver

    if(quantRequisicoes){
        printf("Qual e o codigo da requisicao?: ");
        lerString(codigo,MAX_CODIGOREQ);
        posReq = procuraRequisicao(codigo, vRequisicoes, quantRequisicoes);

        if(posReq!=-1 && vRequisicoes[posReq].estadoRequisicao == 1){
            printf("Data de devolucao:\n");
            vRequisicoes[posReq].dataDevolucao = lerData();

            diasDevolucao = converteDataDias(vRequisicoes[posReq].dataDevolucao);
            diasRequisicao = converteDataDias(vRequisicoes[posReq].dataRequisicao);

            if(diasDevolucao>diasRequisicao){//verifica se a data de devolucao é posterior à data de requisicao

            printf("Local de devolucao(1-Residencias ou 2-Campus1 ou 3-Campus2 ou 4-Campus5): ");
            vRequisicoes[posReq].localDevolucao = lerInteiro(1,4);

            vRequisicoes[posReq].estadoRequisicao = 2;

            vRequisicoes[posReq].multa = calculaMulta(vRequisicoes[posReq].dataRequisicao, vRequisicoes[posReq].dataDevolucao, vRequisicoes[posReq].prazo, &vRequisicoes[posReq].duracao);

            printf("\nMulta a pagar: %d euro\n", vRequisicoes[posReq].multa);

            posPort = procuraPortatil(vRequisicoes[posReq].num, vPortateis, quantPortateis);

            vPortateis[posPort].estado = 1; // coloca o portatil disponivel

            vPortateis[posPort].local = vRequisicoes[posReq].localDevolucao; // muda o local do portatil para o local onde foi devolvido

            vPortateis[posPort].quantDiasRequisitado += vRequisicoes[posReq].duracao; // acrescenta a duracao da requisicao no contador de dias em que esteve requisitado

            atualizaLog(vRequisicoes[posReq],vPortateis[posPort]); // escreve a informacao no ficheiro

            }
            else{
                printf("A data inserida nao e valida (anterior a data de requisicao)...\n");
            }
        }
        else{
            printf("A requisicao com esse codigo nao existe...\n");
        }

    }
    else{
        printf("\nNao existem portateis requisitados...\n");
    }

}

/********************************************************************************************************
Funcao mostrarRequisicoes
Descricao: Mostra os detalhes de todas as requicoes.
Aceita como parametros o vetor vRequisicoes e o inteiro quantRequisicoes.
Não devolve nenhum dado (tipo void)
********************************************************************************************************/
void mostrarRequisicoes(tipoRequisicao *vRequisicoes, int quantRequisicoes){
    int i;

    if(quantRequisicoes==0){
        printf("\nNao existem requisicoes...\n");
    }
    else{

        for(i=0;i<quantRequisicoes;i++){
            mostraRequisicao(vRequisicoes[i]);
        }
    }
}


/********************************************************************************************************
Funcao contaRequisicoesAtivas
Descricao: Conta requisicoes ativas.
Aceita como parametros o vetor vRequisicoes e o inteiro quantRequisicoes.
Devolve por "return" o numero de requisicoes ativas
********************************************************************************************************/
int contaRequisicoesAtivas(tipoRequisicao *vRequisicoes, int quantRequisicoes){

    int i;
    int conta = 0;

    for(i=0;i<quantRequisicoes;i++){
        if(vRequisicoes[i].estadoRequisicao == 1){
            conta++;
        }
    }

    return conta;
}


/********************************************************************************************************
Funcao renovarRequicicao
Descricao: Renova uma Requisicao.
Aceita como parametros o vetor vRequisicoes e o inteiro quantRequisicoes.
********************************************************************************************************/
void renovarRequisicao(tipoRequisicao *vRequisicoes, int quantRequisicoes){
    int pos;
    char codigo[MAX_CODIGOREQ];
    int requisicoesAtivas = 0;

    requisicoesAtivas = contaRequisicoesAtivas(vRequisicoes, quantRequisicoes);

    if(requisicoesAtivas==0){
        printf("Nao existem requisicoes ativas...\n");
    }
    else{
        printf("Introduza o codigo da requisicao a renovar: ");
        lerString(codigo,MAX_CODIGOREQ);
        pos = procuraRequisicao(codigo,vRequisicoes,quantRequisicoes);
        if(pos==-1 || vRequisicoes[pos].estadoRequisicao == 2){
            printf("Nao existe nenhuma requisicao ativa de um portatil com esse numero...\n");
        }
        else{
            vRequisicoes[pos].prazo+=7;
            printf("Renovacao feita com sucesso\n");
        }
    }
}


/********************************************************************************************************
Funcao calculaMulta
Descricao: Calcula a multa a pagar.
Aceita como parametros as estruturas do tipodata dataRequisicao e dataDevolucao e o inteiro prazo.
Devolve por "return" a multa a pagar.
********************************************************************************************************/
int calculaMulta(tipoData dataRequisicao, tipoData dataDevolucao, int prazo, int *diasDiferenca){

    int diasDevolucao;
    int diasRequisicao; // variaveis que guardam o numero do dia em relacao à mesma data
    int multa = 0; // multa

    diasRequisicao = converteDataDias(dataRequisicao);
    diasDevolucao = converteDataDias(dataDevolucao);

    *diasDiferenca = diasDevolucao-diasRequisicao;

    if(*diasDiferenca > prazo){
        multa = (*diasDiferenca - prazo) * 10;
    }

    return multa;
}


/********************************************************************************************************
Funcao atualizaLog
Descricao: Acrescenta no ficheiro Log.txt informacoes sobre uma devolucao.
Aceita como parametros a estrutura do tipo tipoRequisicao requisicao e a estrutura do tipo tipoPortatil portatil
********************************************************************************************************/
void atualizaLog(tipoRequisicao requisicao, tipoPortatil portatil){

    FILE *ficheiro;
    int erro;

    ficheiro = fopen("Log.txt","a");

    if(ficheiro != NULL){
        fprintf(ficheiro,"\nREQUISICAO CODIGO %s:\n",requisicao.codigo);
        fprintf(ficheiro,"\tNumero do portatil: %d\n",requisicao.num);
        fprintf(ficheiro,"\tDesignacao: %s\n", portatil.designacao);
        fprintf(ficheiro,"\tProcessador: %s\n",portatil.processador);
        fprintf(ficheiro,"\tRAM: %d GB\n", portatil.ram);
        fprintf(ficheiro,"\tNome do utente: %s\n",requisicao.nomeUtente);

        switch(requisicao.tipoUtente){
            case 1:
                fprintf(ficheiro,"\tTipo de utente: Estudante\n");
                break;
            case 2:
                fprintf(ficheiro,"\tTipo de utente: Docente\n");
                break;
            default:
                fprintf(ficheiro,"\tTipo de utente: Tecnico administrativo\n");
        }

        fprintf(ficheiro,"\tData da requisicao: %d - %d - %d\n",requisicao.dataRequisicao.dia,requisicao.dataRequisicao.mes,requisicao.dataRequisicao.ano);
        fprintf(ficheiro,"\tPrazo da requisicao: %d dias\n",requisicao.prazo);
        fprintf(ficheiro,"\tData de devolucao: %d - %d - %d\n",requisicao.dataDevolucao.dia,requisicao.dataDevolucao.mes,requisicao.dataDevolucao.ano);
        fprintf(ficheiro,"\tDuracao: %d dias\n", requisicao.duracao);
        fprintf(ficheiro,"\tMulta: %d euros\n",requisicao.multa);

        switch(requisicao.localDevolucao){
            case 1:
                fprintf(ficheiro,"\tLocal da devolucao: Residencias\n");
                break;
            case 2:
                fprintf(ficheiro,"\tLocal da devolucao: Campus 1\n");
                break;
            case 3:
                fprintf(ficheiro,"\tLocal da devolucao: Campus 2\n");
                break;
            default:
                fprintf(ficheiro,"\tLocal da devolucao: Campus 5\n");
        }

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheiro\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro...\n");
    }

    fclose(ficheiro);

}

/********************************************************************************************************
Funcao procuraDataDevolucaoAnterior
Descricao: Procura a data da ultima devolucao efetuada no vetor vRequisicoes.
Aceita como parametros o vetor vRequisicoes e o inteiro quantRequisicoes e o inteiro num.
Devolve a data da ultima devolucao efetuada.
********************************************************************************************************/
tipoData procuraDataDevolucaoAnterior(tipoRequisicao *vRequisicao, int quantRequisicao, int num){

    int i;
    tipoData dataAnterior;
    dataAnterior.ano = 0;
    dataAnterior.mes = 0;
    dataAnterior.dia = 0;

    for(i=0; i<quantRequisicao; i++){
        if((vRequisicao[i].num == num) && (vRequisicao[i].estadoRequisicao == 2)){
            dataAnterior.dia = vRequisicao[i].dataDevolucao.dia;
            dataAnterior.mes = vRequisicao[i].dataDevolucao.mes;
            dataAnterior.ano = vRequisicao[i].dataDevolucao.ano;
        }
    }

    return dataAnterior;
}

/********************************************************************************************************
Funcao guardarInfoRequisicoes
Descricao: Guarda a informacao sobre as requisicoes num ficheiro binario.
Aceita como parametros o vetor vRequisicoes e o inteiro quantRequisicoes.
Não devolve nada(tipo void)
********************************************************************************************************/
void guardarInfoRequisicoes(tipoRequisicao *vRequisicoes,int quantRequisicoes){

    FILE *ficheiro;
    int erro;

    ficheiro = fopen("InfoRequisicoes.dat","wb");

    if(ficheiro != NULL){

        fwrite(&quantRequisicoes,sizeof(int),1,ficheiro);
        fwrite(vRequisicoes,sizeof(tipoRequisicao),quantRequisicoes,ficheiro);

        printf("Informacao guardada com sucesso!(informacao requisicoes)\n");

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheiro(informacao requisicoes)\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro(informacao requisicoes)...");
    }

}

/********************************************************************************************************
Funcao *lerInfoRequisicoes
Descricao: Lê a informacao sobre as requisicoes de um ficheiro binario.
Aceita como parametros de entrada o vetor dinamico vRequisicoes e o inteiro em *quantRequisicoes.
Devolve "por return": o vetor dinamico.
********************************************************************************************************/
tipoRequisicao *lerInfoRequisicoes(tipoRequisicao *vRequisicoes, int *quantRequisicoes){

    FILE *ficheiro;
    int erro;
    tipoRequisicao *v;
        /*backup do vetor dinamico*/
    v = vRequisicoes;

    ficheiro = fopen("InfoRequisicoes.dat","rb");

    if(ficheiro != NULL){

        fread(&(*quantRequisicoes),sizeof(int),1,ficheiro);

        vRequisicoes = realloc(vRequisicoes,(*quantRequisicoes)*sizeof(tipoRequisicao));

        if(vRequisicoes == NULL && *quantRequisicoes != 0){
            printf("Erro ao alocar memoria(informacao requisicoes)...");
            vRequisicoes = v;
        }
        else{
            fread(vRequisicoes,sizeof(tipoRequisicao),*quantRequisicoes,ficheiro);

            printf("Informacao lida com sucesso!(informacao requisicoes)\n");
        }

        erro = fclose(ficheiro);
        if(erro != 0){
            printf("Erro %d no fecho ficheiro(informacao requisicoes)\n",erro);
        }
    }
    else{
        printf("Erro ao abrir ficheiro(informacao requisicoes)...");
    }

    return vRequisicoes;
}

/********************************************************************************************************
Funcao mostraRequisicao
Descricao: Mostra os dados de uma requisicao
Aceita como parametros a estrutura do tipo tipoRequisicao requisicao.
Não devolve nada(tipo void)
********************************************************************************************************/
void mostraRequisicao(tipoRequisicao requisicao){

            printf("\n\tREQUISICAO CODIGO %s:\n",requisicao.codigo);
            printf("\tNumero do portatil: %d\n",requisicao.num);
            printf("\tNome do utente: %s\n",requisicao.nomeUtente);

            switch(requisicao.tipoUtente){
                case 1:
                    printf("\tTipo de utente: Estudante\n");
                    break;
                case 2:
                    printf("\tTipo de utente: Docente\n");
                    break;
                default:
                    printf("\tTipo de utente: Tecnico administrativo\n");
            }

            printf("\tData da requisicao: %d - %d - %d\n",requisicao.dataRequisicao.dia,requisicao.dataRequisicao.mes,requisicao.dataRequisicao.ano);
            printf("\tPrazo da requisicao: %d dias\n",requisicao.prazo);

            switch(requisicao.estadoRequisicao){
                case 1:
                    printf("\tEstado da requisicao: Ativa\n");
                    break;

                default:
                    printf("\tEstado da requisicao: Concluida\n");
                    printf("\tData de devolucao: %d - %d - %d\n",requisicao.dataDevolucao.dia,requisicao.dataDevolucao.mes,requisicao.dataDevolucao.ano);
                    printf("\tDuracao: %d dias\n", requisicao.duracao);
                    printf("\tMulta: %d euros\n",requisicao.multa);

                    switch(requisicao.localDevolucao){
                        case 1:
                            printf("\tLocal da devolucao: Residencias\n");
                            break;
                        case 2:
                            printf("\tLocal da devolucao: Campus 1\n");
                            break;
                        case 3:
                            printf("\tLocal da devolucao: Campus 2\n");
                            break;
                        default:
                            printf("\tLocal da devolucao: Campus 5\n");
                    }
            }
}

/********************************************************************************************************
Funcao mostrarUmaRequisicao
Descricao: Mostra os dados de uma requisicao selecionada pelo utilizador
Aceita como parametros o vetor vRequisicoes e o inteiro quantRequisicoes.
Não devolve nada(tipo void)
********************************************************************************************************/
void mostrarUmaRequisicao(tipoRequisicao *vRequisicoes,int quantRequisicoes){
    char codigo[MAX_CODIGOREQ];
    int pos;

    if(quantRequisicoes==0){
        printf("\nNao existem requisicoes...\n");
    }
    else{
        printf("Codigo: ");
        lerString(codigo,MAX_CODIGOREQ);
        pos = procuraRequisicao(codigo,vRequisicoes,quantRequisicoes);
        if(pos==-1){
            printf("Requisicao Inexistente...\n");
        }
        else{
            mostraRequisicao(vRequisicoes[pos]);
        }
    }
}
