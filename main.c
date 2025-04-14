#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024

bool contains_or_equals(const char *line) 
{
    const char *or_ptr = strstr(line, "OR");
    if (!or_ptr) return false;

    if ((or_ptr == line || *(or_ptr - 1) == ' ') &&
        (*(or_ptr + 2) == ' ' || *(or_ptr + 2) == '\'' || *(or_ptr + 2) == '\"')) 
    {
        
        const char *equals_ptr = strchr(or_ptr, '=');
        if (equals_ptr) return true;
    }

    return false;
}

bool is_sqli_line(const char *line) 
{
    const char *sql_keywords[] = 
    {
        "SELECT", "INSERT", "UPDATE", "DELETE",
        "WHERE", "FROM", "UNION", "EXEC", "JOIN"
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

    for (int i = 0; i < sizeof(sql_keywords) / sizeof(sql_keywords[0]); i++) 
    {
        if (strstr(line, sql_keywords[i])) has_sql = true;
    }

    for (int i = 0; i < sizeof(dangerous_functions) / sizeof(dangerous_functions[0]); i++) 
    {
        if (strstr(line, dangerous_functions[i])) has_danger = true;
    }

    for (int i = 0; i < sizeof(input_sources) / sizeof(input_sources[0]); i++) 
    {
        if (strstr(line, input_sources[i])) has_input = true;
    }

    if (contains_or_equals(line)) return true;

    return (has_sql && has_danger) || (has_input && has_sql);
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
        char *comment = strstr(line, "//");
        if (comment) *comment = '\0';

        if (is_sqli_line(line)) 
        {
            printf("SQLi vulnerability at line %d: %s", line_num, line);
        }
        line_num++;
    }

    fclose(fp);
    return 0;
}
