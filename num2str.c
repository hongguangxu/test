#include<stdio.h>
#include<string.h>

int str2intFunc(char* str, int *errno)
{
    int num = 0, sign = 1, 
        len = 0, index = 0;
    if(NULL == str)
    {
        *errno = -1;
        return 0;
    }

    len = strlen(str);
    if('-'==str[index])
    {
        index++;
        sign = -1;
    }
    else if('+' == str[index])
    {
        index++;
        sign = 1;
    }
    else if(((str[index]-'0')>=0)&&((str[index]-'0')<=9))
    {
        sign = 1;
    }
    else
    {
        *errno = -1;
        return 0;
    }
    while(index < len)
    {
        if(((str[index]-'0')>=0)&&((str[index]-'0')<=9))
        {
            num = num*10 + (str[index]-'0');
        }
        else
        {
            *errno = -1;
            return 0;
        }
        index++;
    }
    num = num*sign;
    *errno = 0;
    return num;
}
int main()
{
    char input[10] = {0};
    int number = 0, errno = 0;
    gets(input);
    number = str2intFunc(input, &errno);
    printf("result is num: %d, errno: %d", number, errno);
    return 0;
}
