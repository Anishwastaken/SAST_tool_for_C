#include <stdio.h>
#include <string.h>

int main() {
    char query[256];
    char name[100];

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '1'='1'", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '2'='2'", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' UNION SELECT username, password FROM admins", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' AND '1'='1'", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '\\'1'='1'", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR \"1\"=\"1\"", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s' OR '\\\\'1'='1'", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s'", name);
    printf("%s\n", query);

    scanf("%s", name);
    sprintf(query, "SELECT * FROM users WHERE name = '%s'", name);
    printf("%s\n", query);

    return 0;
}
