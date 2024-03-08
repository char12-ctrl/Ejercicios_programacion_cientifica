#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define tol 1e-6

int eliminacio (int n, double **A);
double ** producteLU (int n, double **A);

int main (void) {
    int i, j, n, k, ctrl = 0;
    double **A, **LU, **prod;
    
    /* lectura de la dimensió */
    printf("Introdueix la dimensió: \n");
    scanf("%d", &n);
    if (n <= 0) return 1;
    
    /* assignació de memòria dinàmica */
    A = (double **) malloc (n * sizeof(double *));
    if (A == NULL) return 1;
    for (i = 0; i < n; i++) {
        A[i] = (double *) malloc (n * sizeof(double));
    }
    for (i = 0; i < n; i++) {
        if (A[i] == NULL) return 1;
    }
    
    LU = (double **) malloc (n * sizeof(double *));
    if (LU == NULL) return 1;
    for (i = 0; i < n; i++) {
        LU[i] = (double *) malloc (n * sizeof(double));
    }
    for (i = 0; i < n; i++) {
        if (LU[i] == NULL) return 1;
    }
    
    /* lectura dels coeficients de la matriu A */
    printf("Introdueix els coeficients de la matriu: \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
    
    /* càlcul del producte LU */
    LU = A;
    k = eliminacio(n, LU);
    if (k == -1) {
        /* s'ha pogut portar a terme la transformació */
        LU = producteLU(n, LU);
        
        /* càlcul de la resta A - LU */
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (fabs(A[i][j] - LU[i][j]) >= tol) {
                    ctrl = 1;
                    /* si tots els elements són zero, ctrl mantindrà el seu valor inicial que és 0 */
                }
            }
        }
        if (ctrl == 0) {
            printf("El mètode ha funcionat correctament. \n");
            
            /* matriu L */
            printf("La matriu L és: \n");
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    if (i > j) {
                        printf(" %lf ", A[i][j]);
                    } else if (i == j) {
                        printf(" %lf ", 1.);
                    } else {
                        printf(" %lf ", 0.);
                    }
                    printf("\n");
                }
            }
            printf("\n");
            
            /* matriu U */
            printf("La matriu U és: \n");
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    if (i > j) {
                        printf(" %lf ", 0.);
                    } else {
                        printf(" %lf ", A[i][j]);
                    }
                    printf("\n");
                }
            }
            printf("\n");
        } else {
            printf("El mètode no ha funcionat. \n");
        }
    } else {
        printf("No s'ha pogut portar a terme la transformació de la matriu. \n");
    }
    
    /* alliberament de memòria */
    for (i = 0; i < n; i++) {
        free(A[i]);
        free(LU[i]);
        free(prod[i]);
    }
    free(A);
    free(LU);
    free(prod);
    
    return 0;
}

int eliminacio (int n, double **A) {
    int i, j, k;
    
    for (k = 0; k < n - 1; k++) {
        if (fabs(A[k][k]) < tol) {
            /* dividim entre 0 */
            return k;
        }
        for (i = k + 1; i < n; i++) {
            A[i][k] /= A[k][k];
            for (j = k + 1; j < n; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
    
    return -1;
}


double ** producteLU (int n, double **A) {
    int i, j, k;
    double **prod;
    
    /* assignació de memòria dinàmica a LU */
    prod = (double **) malloc (n * sizeof(double *));
    if (prod == NULL) exit(1);
    for (i = 0; i < n; i++) {
        prod[i] = (double *) malloc (n * sizeof(double));
    }
    for (i = 0; i < n; i++) {
        if (prod[i] == NULL) exit(1);
    }
    
    /* càlcul del producte */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            prod[i][j] = 0;
            for (k = 0; k < n; k++) {
                if (i > k) {                /* L[i][k] = A[i][k] */
                    if (k <= j) {           /* U[k][j] = A[k][j] */
                        prod[i][j] += A[i][k] * A[k][j];
                    } else {                /* U[k][j] = 0 */
                        prod[i][j] += 0;
                    }
                } else if (i == k) {         /* L[i][k] = 1 */
                    if (k <= j) {
                        prod[i][j] += A[k][j];
                    } else {
                        prod[i][j] += 0;
                    }
                } else {                    /* L[i][j] = 0 */
                    prod[i][j] += 0;
                }
            }
        }
    }
    
    return prod;
}
