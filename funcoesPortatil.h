#ifndef FUNCOESPORTATIL_H_INCLUDED
#define FUNCOESPORTATIL_H_INCLUDED

#include "constantes.h"
#include "funcoesLeitura.h"
#include "funcoesRequisicao.h"

int lerDadosPortatil(tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis);
void mostrarPortateis(tipoPortatil vPortatil[MAX_PORTATEIS],int quantPortateis,tipoRequisicao *vRequisicoes, int quantRequisicoes);
int procuraPortatil (int numero,tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis);
int contaPortateisDisponiveis(tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis);
void mudarLocalizacao(tipoPortatil vPortateis[MAX_PORTATEIS],int quantPortateis);
void guardarInfoPortateis(tipoPortatil vPortateis[MAX_PORTATEIS], int quantPortateis);
void lerInfoPortateis(tipoPortatil vPortateis[MAX_PORTATEIS], int *quantPortateis);

#endif // FUNCOESPORTATIL_H_INCLUDED
