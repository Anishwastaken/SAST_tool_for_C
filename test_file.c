#include <stdio.h>

int main() {
    char input[100];
    char query[200];

    sprintf(query, "SELECT * FROM users WHERE id = %s", input);

    scanf("%s", input);
    printf("SELECT * FROM logs WHERE msg = '%s'", input);

    strcat(query, " OR '1'='1' -- ");

    return 0;
}