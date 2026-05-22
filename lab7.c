#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef struct {
    char name[50];
    char surname[50];
    int birth_year;
} humen;

int main() {
    #ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    #endif
    setlocale(LC_ALL, "");

    const int N = 4;
    humen arr1[N], arr2[N];
    int i, j;
    humen temp;

    for (i = 0; i < N; i++) {
        printf("Имя: "); scanf("%49s", arr1[i].name);
        printf("Фамилия: "); scanf("%49s", arr1[i].surname);
        printf("Год рождения: "); scanf("%d", &arr1[i].birth_year);
    }

    memcpy(arr2, arr1, sizeof(arr1));

    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - 1 - i; j++) {
            if (arr2[j].birth_year > arr2[j + 1].birth_year) {
                temp = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = temp;
            }
        }
    }

    printf("\nРезультат:\n");
    for (i = 0; i < N; i++) {
        printf("%s %s %d\n", arr2[i].name, arr2[i].surname, arr2[i].birth_year);
    }

    while (getchar() != '\n');
    printf("\nНажмите Enter для выхода...");
    getchar();

    return 0;
}
