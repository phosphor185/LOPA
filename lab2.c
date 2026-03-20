#include <stdio.h>

int main() {
    double matrix[3][3];
    int i, j, k;
    
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%Lf", &matrix[i][j]);
        }
 }
 double sum = 0;
 
 for (i = 0; i < 3; i++) {
        sum += matrix[i][i];
    }
 printf("Summa glav diag: %Lf  ", sum);
    double sum2 = 0;
    for (i = 0; i < 3; i++) {
        sum2 += matrix[i][2 - i];
 }
 printf("Summa pob diag: %Lf", sum2);
 
 int res[2][2];
 int matrix2[2][2];
 for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%Lf", &matrix2[i][j]);
        }
 }
 for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            res[i][j] = 0;
            for (k = 0; k < 2; k++) {
                res[i][j] += matrix2[i][k] * matrix2[k][j];
            }
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d ", res[i][j]);
        }
    }

 
    return 0;
}
