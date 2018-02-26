#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE * arquivo;

typedef struct Body
{
    long double Px, Py, Vx, Vy, m;
};


Body * corpos;

/**
    Posição
*/
long double * corpos_px;
long double * corpos_py;

/**
    Vetor velocidade
*/
long double * corpos_vx;
long double * corpos_vy;

/**
    Massa
*/
long double * corpos_m;

unsigned int totalCorpos;
long double tamanhoUniverso;


int init();
