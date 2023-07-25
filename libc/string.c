#include "string.h"
#include "mem.h"
#include <stdint.h>
#include <stddef.h>

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void hex_to_ascii(int n, char str[])
{
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0)
            continue;
        zeros = 1;
        if (tmp > 0xA)
            append(str, tmp - 0xA + 'a');
        else
            append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA)
        append(str, tmp - 0xA + 'a');
    else
        append(str, tmp + '0');
}

/* K&R */
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

void append(char s[], char n)
{
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

// append the src string to the end of the dst string
void strcat(char dst[], char src[])
{
    int dst_len = 0;
    while (dst[dst_len] != '\0')
    {
        dst_len++;
    }

    int i = 0;
    while (src[i] != '\0')
    {
        dst[dst_len] = src[i];
        dst_len++;
        i++;
    }

    dst[dst_len] = '\0';
}

void backspace(char s[])
{
    int len = strlen(s);
    s[len - 1] = '\0';
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char s1[], char s2[])
{
    int i;
    for (i = 0; s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
            return 0;
    }
    return s1[i] - s2[i];
}

// copy a string from one array to another
void strcpy(char dst[], char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

bool starts_with(char s1[], char s2[])
{
    int i;
    for (i = 0; i < strlen(s2); i++)
    {
        if (s1[i] != s2[i])
        {
            return false;
        }
    }

    return true;
}

char *substring(char *src, int startIdx)
{
    int srcLen = strlen(src);

    // Check if startIdx is within the valid range
    if (startIdx >= srcLen || startIdx < 0)
    {
        kprintf("Invalid starting index.\n");
        return NULL;
    }

    // Calculate the length of the substring
    int subLen = srcLen - startIdx;

    // Allocate memory for the substring (+1 for the null-terminator)
    char *substring = (char *)kmalloc((subLen + 1) * sizeof(char));

    // Copy the substring from the source string to the newly allocated memory
    strcpy(substring, src + startIdx);

    // Null-terminate the substring
    substring[subLen] = '\0';

    return substring;
}

int is_delim(char c, const char *delim)
{
    while (*delim)
    {
        if (c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *strtok(char *src, char *dst, char *delim)
{
    static char *last_token_end = NULL;

    if (src != NULL)
        last_token_end = src;

    if (last_token_end == NULL)
        return NULL;

    // Skip leading delimiters
    while (*last_token_end && is_delim(*last_token_end, delim))
        last_token_end++;

    // Check for the end of the string
    if (*last_token_end == '\0')
    {
        last_token_end = NULL;
        return NULL;
    }

    char *token_start = last_token_end;
    while (*last_token_end && !is_delim(*last_token_end, delim))
        last_token_end++;

    if (dst != NULL)
    {
        // Copy the token to the destination buffer
        while (token_start < last_token_end)
            *dst++ = *token_start++;
        *dst = '\0';
    }

    return token_start;
}

/*
Locate last occurrence of a character in a string

ret = a pointer to the last occurence of the character in the string
*/
char *strrchr(char *str, char character)
{
    if (str == NULL)
        return NULL;

    char *last_occurrence = NULL;

    // Iterate through the string until the end
    while (*str != '\0')
    {
        if (*str == character)
            last_occurrence = str; // Update the pointer if character found
        str++;
    }

    // If the character is found, return the pointer to the last occurrence
    // Otherwise, return NULL (i.e., character not found in the string)
    return last_occurrence;
}