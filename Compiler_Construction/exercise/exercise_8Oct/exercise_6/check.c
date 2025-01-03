#include <stdio.h>
#include <string.h>

int check(char *nr) {
    int sum = 0;

       for (int i = 0; i < strlen(nr); i++) {
   
        if (nr[i] >= '0' && nr[i] <= '9') {
            sum += nr[i];
        }
    }

    return (sum % 3 == 0) ? 1 : 0;
}
