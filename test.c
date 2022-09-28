#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(){
    char *s = malloc(10 * sizeof(char));
    printf("%d\n", sizeof(s));
    s[0] = 'a';
    s[1] = '\0';
    printf("s:%s len:%d size:%d\n", s, strlen(s), sizeof(s));
}
