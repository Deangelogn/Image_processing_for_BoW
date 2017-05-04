//
// Created by eu on 28/04/17.
//

#include <stdio.h>
#include "../header/stringManipulation.h"
#include <memory.h>
#include <stdlib.h>

double getNumber(char *str){
    double result=0;
    while (*str){
        if(*str>='0' && *str<='9') {
            result = result * 10 + (*str - '0');
        }
        str++;
    }
    return result;
}

char* strAppend(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    return strcat(strcpy(ret, a) ,b);
}

char* num2str(int num, int digitis){
    char *str=malloc(digitis+1);
    sprintf(str,"%d",num);
    int dec = 10;
    for (int i = 1; i < digitis; ++i) {
        if(num<dec){
            str = strAppend("0",str);
        }
        dec *= 10;
    }
    return str;
    //}
}