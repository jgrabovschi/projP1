#ifndef FUNCOESLEITURA_H_INCLUDED
#define FUNCOESLEITURA_H_INCLUDED

#include "constantes.h"

void limpaBufferStdin (void);
float lerFloat(float min, float max);
void lerString(char vetor[], int max);
int lerInteiro(int min, int max);
tipoData lerData();
int maxDiasMes(int mes, int ano);
int converteDataDias(tipoData data);

#endif // FUNCOESLEITURA_H_INCLUDED
