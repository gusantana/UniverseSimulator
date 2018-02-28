#include "nbody.h"

int pre_init () {
    arquivo = fopen("galaxy.txt", "rt");
    double vx, vy, px, py, m;
    char gif [256];

    if (arquivo) {
        fscanf(arquivo, "%u", &totalCorpos);
        fscanf(arquivo, "%lf", &tamanhoUniverso);

        if (totalCorpos) {
            corpos = malloc (totalCorpos * sizeof (Body));

            corpos_px = calloc (totalCorpos, sizeof (double));
            corpos_py = calloc (totalCorpos, sizeof (double));

            corpos_vx = calloc (totalCorpos, sizeof (double));
            corpos_vy = calloc (totalCorpos, sizeof (double));

            corpos_m = calloc (totalCorpos, sizeof (double));

            for (int i = 0; i < totalCorpos; i++) {
                fscanf (arquivo, "%lf %lf %lf %lf %lf %[^\n]", &px, &py, &vx, &vy, &m, gif);
                corpos_px[i] = px;
                corpos_py[i] = py;
                corpos_vx[i] = vx;
                corpos_vy[i] = vy;
                corpos_m[i] = m;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

void calcular (void **parametros){
    unsigned idThread = 0;
    printf("%u\n", idThread);
    double *px = (double *)parametros[1], *py = (double *)parametros[2], *vx = (double *)parametros[3], *vy = (double *)parametros[4], *m = (double *)parametros[5];
//    double *px, *py, double *vx, double *vy, double *m
    double delta_x, delta_y, a_x, a_y, distancia;

    double G = -6.67408E-11;
    double fx, fy, f;

    for (unsigned frame_atual = 0; frame_atual < frameTotal; frame_atual++) {
        for (int i = 0 + idThread; i < totalCorpos; i = i + 1 + idThread) {
            a_x = a_y = 0.0;
            for (int j = 0; j < totalCorpos; j++) {
                if (i == j) continue;
                delta_x = px[i] - px[j];
                delta_y = py[i] - py[j];
                distancia = sqrt((delta_x * delta_x) + (delta_y * delta_y));
                f = G * ((m[i] * m[j])/(distancia * distancia));
                fx = f * (delta_x / distancia);
                fy = f * (delta_y / distancia);
                a_x = fx/m[i]; // aceleração da componente X
                a_y = fy/m[i]; // aceleração da componente Y
                vx[i] += delta_tempo * a_x;
                vy[i] += delta_tempo * a_y;
            }
        }
        for (int i = 0; i < totalCorpos; i++) {
            px[i] += delta_tempo * vx[i];
            py[i] += delta_tempo * vy[i];
//            if (frame_atual == frameTotal - 1) {
                fprintf(arquivo_saida, "%f %f %f %f %f %s\n", px[i] + 24916394166, py[i] + 24916394166, vx[i], vy[i], m[i], "star.gif");
//            }

        }
        fprintf(arquivo_saida, "\n");
    }
}
