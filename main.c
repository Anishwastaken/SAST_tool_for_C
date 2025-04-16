#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024

bool is_sqli_line(const char *line) 
{
    const char *sql_patterns[] = 
    {
        "SELECT", "INSERT", "UPDATE", "DELETE", 
        "WHERE", "FROM", "UNION", "EXEC", "OR '1'", "--"
    };
    
    const char *dangerous_functions[] = 
    {
        "sprintf", "snprintf", "strcat", "strncat",
        "vsprintf", "fprintf", "printf"
    };

    const char *input_sources[] = 
    {
        "scanf", "fgets", "getenv", "argv", "getchar"
    };

    bool has_sql = false;
    bool has_danger = false;
    bool has_input = false;

    for (int i = 0; i < 10; i++) 
    {
        if (strstr(line, sql_patterns[i])) has_sql = true;
    }

    for (int i = 0; i < 7; i++) 
    {
        if (strstr(line, dangerous_functions[i])) has_danger = true;
    }

    for (int i = 0; i < 5; i++) 
    {
        if (strstr(line, input_sources[i])) has_input = true;
    }

    return (has_sql && has_danger) || (has_input && has_sql);
}

bool has_escaped_input(const char *line) 
{
    return (strstr(line, "\\'") || strstr(line, "\\\"") || strstr(line, "\\\\"));
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <file.c>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) 
    {
        perror("Error");
        return 1;
    }

    char line[MAX_LINE];
    int line_num = 1;

    while (fgets(line, sizeof(line), fp)) 
    {
        char *comment = strchr(line, '/');
        if (comment && comment[1] == '/') 
            *comment = '\0';

        bool found_sqli = false;
        bool found_escaped = false;

        if (is_sqli_line(line)) 
        {
            found_sqli = true;
        }

        if (has_escaped_input(line)) 
        {
            found_escaped = true;
        }

        if (found_sqli || found_escaped) 
        {
            printf("Potential vulnerabilities at Line %d:\n", line_num);
            if (found_sqli) 
                printf("\tSQL Injection detected\n");
            if (found_escaped) 
                printf("\tEscaped Input detected\n");
        }

        line_num++;
    }

    fclose(fp);
    return 0;
}
