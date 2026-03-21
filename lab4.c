#include <stdio.h>
#include "triangle.h"

int main() {
    double a, b, c;
    printf("vvedite dlini storon treug:\n");
    printf("storona a = ");
    scanf("%lf", &a);
    printf("storona b = ");
    scanf("%lf", &b);
    printf("storona c = ");
    scanf("%lf", &c);
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("oshibka\n");
        return 1;
    }
    if (!is_valid_triangle(a, b, c)) {
        printf("oshibka!\n");
        return 1;
    }
    double perimeter = calculate_perimeter(a, b, c);
    double area = calculate_area(a, b, c);
    
    printf("\nres:\n");
    printf("perimetr: %.2f\n", perimeter);
    printf("ploshad: %.2f\n", area);
    
    return 0;
}


#include "triangle.h"
#include <math.h>

int is_valid_triangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

double calculate_perimeter(double a, double b, double c) {
    return a + b + c;
}

double calculate_area(double a, double b, double c) {
    double p = calculate_perimeter(a, b, c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}


#ifndef TRIANGLE_H
#define TRIANGLE_H

double calculate_perimeter(double a, double b, double c);
double calculate_area(double a, double b, double c);
int is_valid_triangle(double a, double b, double c);

#endif    
    return 0;
}
