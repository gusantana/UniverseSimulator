#include "nbody.c"

int main () {
    pre_init();

    char tamanhoUniverso [] = "6521362399";
    arquivo_saida = fopen ("nbody_result.txt", "wt");
    fprintf(arquivo_saida, "%u\n", totalCorpos);
    fprintf(arquivo_saida, "%s\n", tamanhoUniverso);
    void * parametros [6];
    int idThread = 0;
    parametros[0] = &idThread;
    parametros[1] = corpos_px;
    parametros[2] = corpos_py;
    parametros[3] = corpos_vx;
    parametros[4] = corpos_vy;
    parametros[5] = corpos_m;
    calcular(parametros);
//    calcular (0, corpos_px, corpos_py, corpos_vx, corpos_vy, corpos_m);

    fclose(arquivo_saida);
    return 0;
}
