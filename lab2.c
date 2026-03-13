#include <stdio.h>

int main() {
    int n = 9;
    scanf("%d", &n);
    int arr[n]; 

    printf("Vvedite %Lm elementov:\n", n);
    for(i = 0, i < n; i++) {
    	scanf("%Lm", &arr[i]);
	}
}
