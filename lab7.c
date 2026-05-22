#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef struct {
    char name[50];
    char surname[50];
    int birth_year;
} humen;

int main() {
    // --- ОБЪЯВЛЕНИЕ ВСЕХ ПЕРЕМЕННЫХ В НАЧАЛЕ ---
    FILE *f = NULL;
    humen *arr1 = NULL;
    humen *arr2 = NULL;
    humen temp;
    int i, j;
    int count = 0;
    int capacity = 4;
    char buf_name[50], buf_surname[50];
    int buf_year;

    // Настройка кодировки консоли для кириллицы
    #ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    #endif
    setlocale(LC_ALL, "");

    // 1. Открытие файла
    f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("Ошибка: не удалось открыть файл data.txt\n");
        printf("Создайте файл data.txt в папке с программой.\n");
        printf("Формат: Имя Фамилия Год (каждый с новой строки)\n");
        while (getchar() != '\n'); getchar();
        return 1;
    }

    // 2. Выделение памяти под первый массив
    arr1 = (humen*)malloc(capacity * sizeof(humen));
    if (arr1 == NULL) {
        printf("Ошибка выделения памяти\n");
        fclose(f);
        while (getchar() != '\n'); getchar();        return 1;
    }

    // 3. Чтение данных из файла (до конца или до ошибки формата)
    while (fscanf(f, "%49s %49s %d", buf_name, buf_surname, &buf_year) == 3) {
        // Если места мало -> удваиваем ёмкость массива
        if (count == capacity) {
            capacity *= 2;
            arr1 = (humen*)realloc(arr1, capacity * sizeof(humen));
            if (arr1 == NULL) {
                printf("Ошибка выделения памяти\n");
                fclose(f);
                while (getchar() != '\n'); getchar();
                return 1;
            }
        }
        strncpy(arr1[count].name, buf_name, 49);
        arr1[count].name[49] = '\0';
        strncpy(arr1[count].surname, buf_surname, 49);
        arr1[count].surname[49] = '\0';
        arr1[count].birth_year = buf_year;
        count++;
    }
    fclose(f);

    if (count == 0) {
        printf("Файл пуст или содержит неверные данные.\n");
        free(arr1);
        while (getchar() != '\n'); getchar();
        return 0;
    }

    // 4. Создание второго массива (точная копия первого)
    arr2 = (humen*)malloc(count * sizeof(humen));
    if (arr2 == NULL) {
        printf("Ошибка выделения памяти\n");
        free(arr1);
        while (getchar() != '\n'); getchar();
        return 1;
    }
    memcpy(arr2, arr1, count * sizeof(humen));

    // 5. Сортировка второго массива пузырьком по году рождения
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (arr2[j].birth_year > arr2[j + 1].birth_year) {
                temp = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = temp;
            }        }
    }

    // 6. Вывод результата
    printf("\nОтсортированный массив (%d записей):\n", count);
    printf("----------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-15s %-15s %d\n", arr2[i].name, arr2[i].surname, arr2[i].birth_year);
    }

    // 7. Очистка памяти
    free(arr1);
    free(arr2);

    // Пауза перед закрытием консоли
    while (getchar() != '\n');
    printf("\nНажмите Enter для выхода...");
    getchar();

    return 0;
}
