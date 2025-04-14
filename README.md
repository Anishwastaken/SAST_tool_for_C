C SAST Detection Tool

A lightweight and efficient Static Application Security Testing (SAST) tool built for C developers. It scans C source code for potential **SQL Injection (SQLi)** vulnerabilities by analyzing unsafe use of user input in SQL queries.

Detects:
Unsafe input sources** (e.g., `scanf`, `fgets`, `getenv`, etc.)
Dangerous string handling functions** (e.g., `sprintf`, `strcat`, etc.)
SQL keywords or patterns** (e.g., `SELECT`, `WHERE`, `OR '1'='1'`, `--`)


 Usage

1. Clone or download this repository.
2. Compile the static analysis tool using:
bash
gcc main.c -o sast
