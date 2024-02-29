#ifndef FUNCOESREQUISICAO_H_INCLUDED
#define FUNCOESREQUISICAO_H_INCLUDED

#include "constantes.h"
#include "funcoesLeitura.h"
#include "funcoesPortatil.h"
#include "funcoesAvaria.h"

tipoRequisicao *registarRequisicao(tipoPortatil vPortateis[MAX_PORTATEIS], tipoRequisicao *vRequisicoes, int quantPortateis, int *quantRequisicoes, tipoAvaria *vAvarias, int quantAvarias);
int procuraRequisicao (char codigo[MAX_CODIGOREQ],tipoRequisicao *vRequisicoes, int quantRequisicoes);
void mostrarRequisicoes(tipoRequisicao *vRequisicoes, int quantRequisicoes);
int contaRequisicoesAtivas(tipoRequisicao *vRequisicoes, int quantRequisicoes);
void renovarRequisicao(tipoRequisicao *vRequisicoes, int quantRequisicoes);
int calculaMulta(tipoData dataRequisicao, tipoData dataDevolucao, int prazo, int *diasDiferenca);
void devolverPortatil(tipoRequisicao *vRequisicoes, int quantRequisicoes, tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis);
void atualizaLog(tipoRequisicao requisicao, tipoPortatil portatil);
tipoData procuraDataDevolucaoAnterior(tipoRequisicao *vRequisicao, int quantRequisicao, int num);
void guardarInfoRequisicoes(tipoRequisicao *vRequisicoes,int quantRequisicoes);
tipoRequisicao *lerInfoRequisicoes(tipoRequisicao *vRequisicoes, int *quantRequisicoes);
void mostraRequisicao(tipoRequisicao requisicao);
void mostrarUmaRequisicao(tipoRequisicao *vRequisicoes,int quantRequisicoes);

#endif // FUNCOESREQUISICAO_H_INCLUDED
