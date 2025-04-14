### SAST Tool in C for Detecting SQL Injection

A simple Static Application Security Testing (SAST) tool written in C to detect potential **SQL Injection vulnerabilities** in C source files.

This tool scans `.c` files for suspicious patterns like use of user input (`scanf`, `argv`, etc.) with SQL keywords in unsafe string operations (`sprintf`, `strcat`, etc.). It also heuristically detects common injection patterns like `OR 1=1`.

### How It Works

The detector looks for:
- SQL keywords: `SELECT`, `INSERT`, `WHERE`, `UNION`, etc.
- Dangerous C functions: `sprintf`, `strcat`, `printf`, etc.
- User input sources: `scanf`, `fgets`, `argv`, `getenv`, etc.
- Suspicious logic like: `OR something = something` (e.g., `OR 2=2`)

If a line contains both SQL logic and either user input or dangerous functions, it is flagged.

### Requirements
- GCC compiler
- C standard library

### Compilation

```bash
gcc main.c -o sqli_detector -Wall

```
### Sample input

```bash
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


```

### Output

```bash

Potential vulnerabilities at Line 9:
        SQL Injection detected
Potential vulnerabilities at Line 14:
        SQL Injection detected
Potential vulnerabilities at Line 17:
        SQL Injection detected
Potential vulnerabilities at Line 19:
        SQL Injection detected
Potential vulnerabilities at Line 24:
        SQL Injection detected
Potential vulnerabilities at Line 29:
        SQL Injection detected
        Escaped Input detected
Potential vulnerabilities at Line 34:
        SQL Injection detected
        Escaped Input detected
Potential vulnerabilities at Line 39:
        SQL Injection detected
        Escaped Input detected
Potential vulnerabilities at Line 44:
        SQL Injection detected
Potential vulnerabilities at Line 49:
        SQL Injection detected
```
