#include "GL/freeglut.h"
#include "nbody.h"

int pre_init () {
    arquivo = fopen("galaxy.txt", "r");
    double vx, vy, px, py, m;
    char gif [256];

    if (arquivo) {
        fscanf(arquivo, "%u", &totalCorpos);
        fscanf(arquivo, "%lf", &tamanhoUniverso);

        if (totalCorpos) {
            corpos = malloc (totalCorpos * sizeof (Body));

            corpos_px = malloc (totalCorpos * sizeof (double));
            corpos_py = malloc (totalCorpos * sizeof (double));

            corpos_vx = malloc (totalCorpos * sizeof (double));
            corpos_vy = malloc (totalCorpos * sizeof (double));

            corpos_m = malloc (totalCorpos * sizeof (double));

            for (int i = 0; i < totalCorpos; i++) {
                fscanf (arquivo, "%lf %lf %lf %lf %lf %s", &px, &py, &vx, &vy, &m, gif);
                corpos_px[i] = corpos.Px = px;
                corpos_py[i] = corpos.Py = py;
                corpos_vx[i] = corpos.Vx = vx;
                corpos_vy[i] = corpos.Vy = vy;
                corpos_m[i] = corpos.m = m;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

void calcular (double *px, double *py, double *vx, double *vy, double *m) {
    double delta_x, delta_y, a_x, a_y, distancia;

    double G = 6.674E-11;
    double fx, fy;
    for (int i = 0; i < totalCorpos; i++) {
        for (int j = 1; i < totalCorpos && i != j; j++) {
            delta_x = px[i] - px[j];
            delta_y = py[i] - py[j];
            distancia = sqrt((delta_x * delta_x) + (delta_y * delta_y));
            fx = ((G * m[i] * m[j])/(distancia * distancia)) * (delta_x / distancia);
            fy = ((G * m[i] * m[j])/(distancia * distancia)) * (delta_y / distancia);
        }
    }
}
