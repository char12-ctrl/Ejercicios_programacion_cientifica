#include <stdio.h>
#define DIM 30

int main (void) {
    int i, j, k, n;
    double A[DIM][DIM], b[DIM], m;
    
    /* lectura de la dimensió, la matriu del sistema i el vector de termes independents */
    do {
        printf("Introdueix la dimensió: \n");
        scanf("%d", &n);
    } while (n <= 0 || n > DIM);
    
    printf("Introdueix els coeficients de la matriu d'un sistema de n equacions i n incògnites: \n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    printf("Introdueix els termes independents: \n");
    for (i = 1; i <= n; i++) {
        scanf("%lf", &b[i]);
    }
    
    /* aplicació de l'algorisme de Gauss o  eliminació gaussiana */
    for (k = 1; k < n; k++) {                   /* pas */
        if (A[k][k] == 0) {
            printf("El mètode no es pot usar com l'expliquem. \n");
            return 1;
        } else {
            for (i = k + 1; i <= n; i++) {      /* fila */
                m = A[i][k] / A[k][k];          /* multiplicador */
                A[i][k] = 0;
                
                for (j = k + 1; j <= n; j++) {  /* columna */
                    A[i][j] -= m * A[k][j];
                }
                
                b[i] -= m * b[k];               /* terme independent */
            }
        }
    }
    
    /* escriptura de la matriu reduïda */
    printf("El sistema reduït és \n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf(" %+lf ", A[i][j]);
        }
        printf(" %lf \n", b[i]);
    }
    printf("\n");
    
    /* solució del sistema mitjançant el mètode de substitució endarrere */
    for (i = n; i > 0; i--) {
        for (j = n; j > i; j--) {
            b[i] -= A[i][j] * b[j];
        }
        b[i] /= A[i][i];
    }
    
    /* escriptura de la solució del sistema */
    printf("La solució és \n");
    for (i = 1; i <= n; i++) {
        printf("x_%d = %+lf \n", i, b[i]);
    }
                
    return 0;
}
