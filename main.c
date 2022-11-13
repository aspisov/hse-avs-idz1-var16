#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void count(char* string, int* digits, int* letters) {
    for (int i = 0; i < strlen(string); i++) 
    {  
        if (string[i] >= '0' && string[i] <= '9') {
            (*digits)++;
        } else if (string[i] >= 'A' && string[i] <= 'Z') {
            (*letters)++;
        } else if (string[i] >= 'a' && string[i] <= 'z') {
            (*letters)++;
        }
    }
}
   
int main()  
{   
    int digits = 0;
    int letters = 0;
    
    char string[10000]; 
    while (fgets(string, 10000, stdin)) {
        count(string, &digits, &letters);
    }
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d", letters);
   
    return 0;  
}  