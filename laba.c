#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SIZE = 3; // Размер матрицы

void swap_rows(double** matrix, int row1, int row2) {
    for (int i = 0; i < SIZE; i++) {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

void print_matrix(double** matrix) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void forward_elimination(double** matrix) {
    for (int row = 0; row < SIZE - 1; row++) {
        if (matrix[row][row] == 0) {
            int i;
            for (i = row + 1; i < SIZE; i++) {
                if (matrix[i][row] != 0) {
                    swap_rows(matrix, row, i);
                    break;
                }
            }

            if (i == SIZE) {
                return;
            }
        }

        for (int col = row + 1; col < SIZE; col++) {
            double multiplier = matrix[col][row] / matrix[row][row];
            for (int i = row; i < SIZE; i++) {
                matrix[col][i] -= multiplier * matrix[row][i];
            }
        }
    }
}

double determinant(double** matrix) {
    double det = 1.0;

    forward_elimination(matrix);

    for (int i = 0; i < SIZE; i++) {
        det *= matrix[i][i];
    }

    return det;
}

double** matrixGenerator(){
    srand(time(NULL));
    double** matrix = (double**)malloc(SIZE*sizeof(double*));;
    for(int i = 0; i < SIZE; i++){
        matrix[i] = (double*)malloc(SIZE*sizeof(double));
        for(int k = 0; k < SIZE; k++){
            matrix[i][k] = rand()%50;
        }
    }
    return matrix;
}

int main() {
    double time_spent = 0.0;

    // double matrix1[SIZE-1][SIZE-1] = {
    //     {1, 2, 3},
    //     {4, 3, 2},
    //     {6, 3, 11}
    // };

    FILE* fileTime = fopen("Time.txt","w");
    FILE* fileSize = fopen("Size.txt","w");

    int startSize = 3;
    int maxSize = 5001;
    for(int i = startSize; i < maxSize; i+=i/3){
        SIZE = i;

        double** matrix = matrixGenerator();

        clock_t begin = clock();
        double det = determinant(matrix);
        clock_t end = clock();

        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        fprintf(fileTime,"%f\n",time_spent);
        fprintf(fileSize,"%d\n",i);
    }
    printf("На последнее вычисление затрачено времени: %f\n", time_spent);

    fclose(fileTime);
    fclose(fileSize);

    return 0;
}