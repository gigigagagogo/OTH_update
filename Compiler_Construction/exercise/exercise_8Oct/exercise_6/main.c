#include <stdio.h>
#include <string.h>

int check(char *);

int main(void) {
    FILE *file;
    char line[256];
    file = fopen("./numbers.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return 1; 
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (check(line)) {
            printf("%s is divisible by 3\n", line);
        }
    }

    fclose(file);
    return 0;
}
