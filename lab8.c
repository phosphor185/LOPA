#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PEOPLE 100
#define NAME_LENGTH 50

typedef struct {
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    int birthYear;
    char gender;
    float height;
} Person;

void sortByField(Person people[], int count, char *fields) {
    Person temp;
    int i, j;
    int sortByYear = 0, sortByName = 0, sortByGender = 0, sortByHeight = 0;
    int cmpResult;
    
    if (strstr(fields, "year") != NULL || strstr(fields, "год") != NULL) 
        sortByYear = 1;
    if (strstr(fields, "name") != NULL || strstr(fields, "имя") != NULL || 
        strstr(fields, "фамилия") != NULL) 
        sortByName = 1;
    if (strstr(fields, "gender") != NULL || strstr(fields, "пол") != NULL) 
        sortByGender = 1;
    if (strstr(fields, "height") != NULL || strstr(fields, "рост") != NULL) 
        sortByHeight = 1;
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            int shouldSwap = 0;
            
            if (sortByYear) {
                cmpResult = people[j].birthYear - people[j+1].birthYear;
                if (cmpResult > 0) 
                    shouldSwap = 1;
                else if (cmpResult < 0) 
                    shouldSwap = 0;
            }
            
            if (!shouldSwap && sortByName) {
                cmpResult = strcmp(people[j].surname, people[j+1].surname);
                if (cmpResult > 0) 
                    shouldSwap = 1;
                else if (cmpResult < 0) 
                    shouldSwap = 0;            }
            
            if (!shouldSwap && sortByGender) {
                if (people[j].gender > people[j+1].gender) 
                    shouldSwap = 1;
            }
            
            if (!shouldSwap && sortByHeight) {
                if (people[j].height > people[j+1].height) 
                    shouldSwap = 1;
            }
            
            if (shouldSwap) {
                temp = people[j];
                people[j] = people[j+1];
                people[j+1] = temp;
            }
        }
    }
}

int main() {
    FILE *file;
    Person people[MAX_PEOPLE];
    int count = 0;
    char sortFields[100];
    int i;
    
    setlocale(LC_ALL, "Russian");
    // или setlocale(LC_ALL, "ru_RU.UTF-8"); для Linux/Mac
    
    file = fopen("people.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    
    while (fscanf(file, "%s %s %d %c %f", 
                  people[count].name, 
                  people[count].surname, 
                  &people[count].birthYear, 
                  &people[count].gender, 
                  &people[count].height) != EOF) {
        count++;
        if (count >= MAX_PEOPLE) 
            break;
    }
    fclose(file);
    
    printf("Файл загружен. Записей: %d\n", count);    printf("\nВведите поля для сортировки:\n");
    printf("  year/год - год рождения\n");
    printf("  name/имя - имя/фамилия\n");
    printf("  gender/пол - пол\n");
    printf("  height/рост - рост\n");
    printf("Можно указать несколько через пробел: ");
    
    scanf("%s", sortFields);
    
    sortByField(people, count, sortFields);
    
    printf("\nОтсортированные данные:\n");
    printf("================================================\n");
    for (i = 0; i < count; i++) {
        printf("%s %s, %d г., пол: %c, рост: %.2f м\n", 
               people[i].name, 
               people[i].surname, 
               people[i].birthYear, 
               people[i].gender, 
               people[i].height);
    }
    printf("================================================\n");
    
    return 0;
}
