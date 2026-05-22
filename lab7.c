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
    FILE *f = NULL;
    humen *arr1 = NULL;
    humen *arr2 = NULL;
    humen temp;
    int i, j;
    int count = 0;
    int n = 4;
    char qwename[20], qwesurname[20];
    int qweyear;

    setlocale(LC_ALL, "Russian");

    f = fopen("data.txt", "r");

    arr1 = (humen*)malloc(n * sizeof(humen));
    
    while (fscanf(f, "%19s %19s %d", qwename, qwesurname, &qweyear) == 3) {
        if (count == n) {
            n *= 2;
            arr1 = (humen*)realloc(arr1, n * sizeof(humen));
        }
        
        strncpy(arr1[count].name, qwename, 19);
        arr1[count].name[19] = '\0';
        strncpy(arr1[count].surname, qwesurname, 19);
        arr1[count].surname[19] = '\0';
        arr1[count].birth_year = qweyear;
        count++;
    }
    fclose(f);

    arr2 = (humen*)malloc(count * sizeof(humen));
    
    memcpy(arr2, arr1, count * sizeof(humen));

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (arr2[j].birth_year > arr2[j + 1].birth_year) {
                temp = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = temp;
            }        }
    }

    printf("\nÐåçóëüòàò:\n", count);
    printf("----------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-15s %-15s %d\n", arr2[i].name, arr2[i].surname, arr2[i].birth_year);
    }

    free(arr1);
    free(arr2);

    while (getchar() != '\n');
    printf("\näëÿ çàêðûòèÿ íàæìèå ýíòåð îê...");
    getchar();

    return 0;
}
