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
gcc newmain.c -o sqli_detector -Wall

```
### Sample input

```bash

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

```

### Output

```bash

SQLi vulnerability at line 7:     sprintf(query, "SELECT * FROM users WHERE id = %s", input);
SQLi vulnerability at line 10:     printf("SELECT * FROM logs WHERE msg = '%s'", input);
SQLi vulnerability at line 12:     strcat(query, " OR '1'='1' -- ");

```
