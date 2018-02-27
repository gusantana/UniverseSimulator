#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE * arquivo;

unsigned int delta_tempo = 200000;

unsigned int frameTotal = 1000;

typedef struct Body
{
    long double Px, Py, Vx, Vy, m;
} Body;


Body * corpos;

/**
    Posição
*/
double * corpos_px;
double * corpos_py;

/**
    Vetor velocidade
*/
double * corpos_vx;
double * corpos_vy;

/**
    Massa
*/
double * corpos_m;

unsigned int totalCorpos    = 0;
double tamanhoUniverso      = 0.0;

int pre_init();
double **frames;
