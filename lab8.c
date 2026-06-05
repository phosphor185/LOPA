#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define DLINA_IMENI 50
#define MAKS_LUDEY 100

typedef struct {
    char imya[DLINA_IMENI];
    char familiya[DLINA_IMENI];
    int god_rozhdeniya;
    char pol;
    float rost;
} Chelovek;

void sortirovat_po_polyu(Chelovek lyudi[], int schet, char *polya) {
    Chelovek vrem;
    int i, j;
    int sort_po_godu = 0, sort_po_imeni = 0, sort_po_polu = 0, sort_po_rostu = 0;
    int rezultat_sravneniya;
    
    if (strstr(polya, "god") != NULL || strstr(polya, "year") != NULL) 
        sort_po_godu = 1;
    if (strstr(polya, "imya") != NULL || strstr(polya, "familiya") != NULL || 
        strstr(polya, "name") != NULL) 
        sort_po_imeni = 1;
    if (strstr(polya, "pol") != NULL || strstr(polya, "gender") != NULL) 
        sort_po_polu = 1;
    if (strstr(polya, "rost") != NULL || strstr(polya, "height") != NULL) 
        sort_po_rostu = 1;
    
    for (i = 0; i < schet - 1; i++) {
        for (j = 0; j < schet - 1 - i; j++) {
            int nuzhno_menyat = 0;
            
            if (sort_po_godu) {
                rezultat_sravneniya = lyudi[j].god_rozhdeniya - lyudi[j+1].god_rozhdeniya;
                if (rezultat_sravneniya > 0) 
                    nuzhno_menyat = 1;
                else if (rezultat_sravneniya < 0) 
                    nuzhno_menyat = 0;
            }
            
            if (!nuzhno_menyat && sort_po_imeni) {
                rezultat_sravneniya = strcmp(lyudi[j].familiya, lyudi[j+1].familiya);
                if (rezultat_sravneniya > 0) 
                    nuzhno_menyat = 1;
                else if (rezultat_sravneniya < 0) 
                    nuzhno_menyat = 0;
            }
            
            if (!nuzhno_menyat && sort_po_polu) {
                if (lyudi[j].pol > lyudi[j+1].pol) 
                    nuzhno_menyat = 1;
            }
            
            if (!nuzhno_menyat && sort_po_rostu) {
                if (lyudi[j].rost > lyudi[j+1].rost) 
                    nuzhno_menyat = 1;
            }
            
            if (nuzhno_menyat) {
                vrem = lyudi[j];
                lyudi[j] = lyudi[j+1];
                lyudi[j+1] = vrem;
            }
        }
    }
}

int main() {
    FILE *fayl;
    char polya_sortirovki[100];
    Chelovek lyudi[MAKS_LUDEY];
    int schet = 0;
    int i;
    
    setlocale(LC_ALL, "Russian");
    
    fayl = fopen("people.txt", "r");
    if (fayl == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    
    while (fscanf(fayl, "%s %s %d %c %f", 
                  lyudi[schet].imya, 
                  lyudi[schet].familiya, 
                  &lyudi[schet].god_rozhdeniya, 
                  &lyudi[schet].pol, 
                  &lyudi[schet].rost) != EOF) {
        schet++;
        if (schet >= MAKS_LUDEY) 
            break;
    }
    fclose(fayl);
    
    printf("Файл загружен. Записей: %d\n", schet);
    printf("\nВведите поля для сортировки:\n");
    printf("  god/год - год рождения\n");
    printf("  imya/имя - имя/фамилия\n");
    printf("  pol/пол - пол\n");
    printf("  rost/рост - рост\n");
    printf("Можно указать несколько через пробел: ");
    
    scanf("%s", polya_sortirovki);
    
    sortirovat_po_polyu(lyudi, schet, polya_sortirovki);
    
    printf("\nОтсортированные данные:\n");
    printf("================================================\n");
    for (i = 0; i < schet; i++) {
        printf("%s %s, %d г., пол: %c, рост: %.2f м\n", 
               lyudi[i].imya, 
               lyudi[i].familiya, 
               lyudi[i].god_rozhdeniya, 
               lyudi[i].pol, 
               lyudi[i].rost);
    }
    printf("================================================\n");
    
    return 0;
}
