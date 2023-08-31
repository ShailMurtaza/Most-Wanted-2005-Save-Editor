#include <stdlib.h>
#include <string.h>
#ifndef MY_STR_H_
#define MY_STR_H_

char *my_strcat(const char *str1, const char *str2) {
    char *str = NULL; // char pointer
    size_t str_len, str1_len, str2_len; // Length of all strings

    str1_len = strlen(str1);
    str2_len = strlen(str2);
    str_len = str1_len + str2_len;

    str = malloc(str_len + 1); // +1 for \0

    memcpy(str, str1, str1_len); // copy str1
    memcpy(str+str1_len, str2, str2_len+1); // copy str2+1 for copy \0
    return str;
}
#endif
