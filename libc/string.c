#include "string.h"
#include <stdint.h>

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

#define false 0
#define true 1

int starts_with(char s1[], char s2[])
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

void substring(char *src, int startIdx, char *dst)
{
    int length = strlen(src);
    int i, j;

    // Check if the start index is within the bounds of the source string
    if (startIdx >= length)
    {
        strcpy(dst, ""); // If startIdx is beyond the string length, return an empty string
        return;
    }

    // Copy characters from startIdx until the end of the string
    for (i = startIdx, j = 0; src[i] != '\0'; i++, j++)
    {
        dst[j] = src[i];
    }

    dst[j] = '\0'; // Null-terminate the destination string
}