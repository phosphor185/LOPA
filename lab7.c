#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    char name[50];
    char surname[50];
    int birth_year;
} humen;

int main() {
    setlocale(LC_ALL, ""); // Корректная локаль для вывода кириллицы

    FILE *f = fopen("data.txt", "r");
    if (!f) {
        printf("Ошибка: не удалось открыть файл data.txt\n");
        return 1;
    }

    /* === 1 ПЕРВЫЙ ПРОХОД: считаем количество корректных строк === */
    int count = 0;
    char tmp_name[20], tmp_surname[20];
    int tmp_year;

    // fscanf пропускает пустые строки и считает только полные записи (3 поля)
    while (fscanf(f, "%19s %19s %d", tmp_name, tmp_surname, &tmp_year) == 3) {
        count++;
    }

    if (count == 0) {
        printf("Файл пуст или не содержит корректных данных.\n");
        fclose(f);
        return 0;
    }

    printf("Найдено записей: %d\n", count);

    /* === 2 СТРОГОЕ ВЫДЕЛЕНИЕ ПАМЯТИ === */
    humen *arr = (humen*)malloc(count * sizeof(humen));
    if (!arr) {
        printf("Ошибка выделения памяти\n");
        fclose(f);
        return 1;
    }

    /* === 3 ВТОРОЙ ПРОХОД: читаем данные в выделенный массив === */
    rewind(f); // Возвращаем указатель в начало файла
    for (int i = 0; i < count; i++) {
        if (fscanf(f, "%49s %49s %d", arr[i].name, arr[i].surname, &arr[i].birth_year) != 3) {
            count = i; // На случай, если файл изменился между проходами
            break;
        }
    }
    fclose(f);

    /* === 4 СОРТИРОВКА (in-place, без arr2) === */
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (arr[j].birth_year > arr[j + 1].birth_year) {
                humen temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    /* === 5 ВЫВОД РЕЗУЛЬТАТА === */
    printf("\nРезультат (%d записей):\n", count);
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-20s %d\n", arr[i].name, arr[i].surname, arr[i].birth_year);
    }

    free(arr);

    printf("\nДля закрытия нажмите Enter...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // очистка буфера ввода
    getchar();

    return 0;
}
