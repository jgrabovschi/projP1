#ifndef FUNCOESAVARIA_H_INCLUDED
#define FUNCOESAVARIA_H_INCLUDED

#include "funcoesLeitura.h"
#include "funcoesPortatil.h"
#include "funcoesRequisicao.h"

tipoAvaria *registarAvaria(tipoPortatil *vPortateis, int quantPortateis, tipoAvaria *vAvarias, int *quantAvarias, tipoRequisicao *vRequisicoes, int quantRequisicoes);
int procuraAvaria (int numero,tipoAvaria *vAvarias, int quantAvarias);
void registarReparacao(tipoAvaria *vAvarias, int quantAvarias, tipoPortatil *vPortateis, int quantPortateis);
void mostraAvaria(tipoAvaria *vAvarias, int quantAvarias);
tipoData procuraDataAvariaAnterior(tipoAvaria *vAvarias, int quantAvarias, int num);
void guardarInfoAvarias(tipoAvaria *vAvarias,int quantAvarias);
tipoAvaria *lerInfoAvarias(tipoAvaria *vAvarias, int *quantAvarias);


#endif // FUNCOESAVARIA_H_INCLUDED
