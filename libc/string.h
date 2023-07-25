#ifndef STRINGS_H
#define STRINGS_H

#include <stdbool.h>

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
void strcat(char dst[], char src[]);
int strcmp(char s1[], char s2[]);
bool starts_with(char s1[], char s2[]);
char *substring(char *src, int startIdx);
char *strtok(char *src, char *dst, char *delim);
char *strrchr(char *str, char character);

#endif
