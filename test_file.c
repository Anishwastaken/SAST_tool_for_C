#include <stdio.h>
#include <string.h>

int main() {
    char query[256];
    char name[100];
    printf("Test 1: Vulnerable code with SQL Injection\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '1'='1'", name);
    printf("%s\n", query);

    printf("\nTest 2: Vulnerable code with SQL Injection (OR 2=2)\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '2'='2'", name);
    printf("%s\n", query);

    printf("\nTest 3: Vulnerable code with UNION SELECT\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' UNION SELECT username, password FROM admins", name);
    printf("%s\n", query);

    printf("\nTest 4: Vulnerable code with AND 1=1\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' AND '1'='1'", name);
    printf("%s\n", query);

    printf("\nTest 5: Escaped single quote in input\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '\\'1'='1'", name);
    printf("%s\n", query);

    printf("\nTest 6: Escaped double quote in input\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR \"1\"=\"1\"", name);
    printf("%s\n", query);

    printf("\nTest 7: Escaped backslash in input\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '\\\\'1'='1'", name);
    printf("%s\n", query);

    printf("\nTest 8: Safe input (no injection)\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s'", name);
    printf("%s\n", query);

    printf("\nTest 9: Safe input with spaces (no injection)\n");
    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s'", name);
    printf("%s\n", query);

    return 0;
}
