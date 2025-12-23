#include <stdio.h>

void inputMatrix(int matrix[3][3], char name) {
    int i, j;
    printf("Enter 3x3 Matrix %c:\n", name);
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            scanf("%d", &matrix[i][j]);
}

void displayMatrix(int matrix[3][3]) {
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void addMatrix(int A[3][3], int B[3][3], int R[3][3]) {
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            R[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrix(int A[3][3], int B[3][3], int R[3][3]) {
    int i, j, k;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            R[i][j] = 0;
            for(k = 0; k < 3; k++)
                R[i][j] += A[i][k] * B[k][j];
        }
    }
}

void transposeMatrix(int A[3][3], int R[3][3]) {
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            R[j][i] = A[i][j];
}

int main() {
    int A[3][3], B[3][3], R[3][3];

    inputMatrix(A, 'A');
    inputMatrix(B, 'B');

    printf("\nMATRIX ADDITION\n");
    addMatrix(A, B, R);
    printf("Result of Addition:\n");
    displayMatrix(R);

    printf("\nMATRIX MULTIPLICATION\n");
    multiplyMatrix(A, B, R);
    printf("Result of Multiplication:\n");
    displayMatrix(R);

    printf("\nMATRIX TRANSPOSE\n");
    transposeMatrix(A, R);
    printf("Transpose of the Matrix:\n");
    displayMatrix(R);

    return 0;
}