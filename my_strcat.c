#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strcat(const char *str1, const char *str2) {
    char *str = NULL; // char pointer
    size_t str_len, str1_len, str2_len;
    int a = 123;

    str1_len = strlen(str1);
    str2_len = strlen(str2);
    str_len = str1_len + str2_len;

    str = malloc(str_len + 1); // +1 for \0

    memcpy(str, str1, str1_len); // copy str1
    memcpy(str+str1_len, str2, str2_len+1); // copy str2+1 for copy \0
    printf("NEW STRLEN: %u\nSTR: %x\n", str_len, str);
    return str;
}

int main() {
    char *str = NULL;
    char str1[] = "a";
    char str2[] = " b";

    str = my_strcat(str1, str2);
    printf("STR: %x\n", str);
    printf("#STR: %s#\n", str);
    return 0;
}

