/*
** EPITECH PROJECT, 2026
** my_strdup
** File description:
** dup a string
*/

#include "myworld.h"

char *my_strdup(char *str)
{
    char *string = NULL;
    int i = 0;
    int len = my_strlen(str);

    string = malloc((unsigned long)len + 1);
    if (string == NULL)
        return NULL;
    while (i < len) {
        string[i] = str[i];
        i += 1;
    }
    string[i] = '\0';
    return string;
}
