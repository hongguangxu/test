#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* decodeStr(char* src)
{
    int N = 0, len = 0;
    int index = 0, temp = 0;
    if(NULL == src)
    {
        return NULL;
    }
    len = strlen(src);
    char tempStr[100] = {0};
    char* dst = NULL;
    int locN = 1, digit = 0, sq = 0, tmpLen = 0, accLen = 0, sub = 0, i=0;
    while(index < len)
    {
        if(((src[index]-'0')>=0)&&((src[index]-'0')<=9))
        {
            if(0==digit)
            {
                //there are str without repeat
                if(0!=sub)
                {
                    tempStr[sub] = '\0';
                    if(NULL==dst)
                    {
                        dst = (char*)malloc(sub*locN);
                    }
                    else
                    {
                        dst = (char*)realloc(dst, sub*locN+accLen);
                    }
                    strcat(dst, tempStr);
                    accLen += sub*locN;
                    sub = 0;
                }
                locN = src[index]-'0'; 
                digit = 1;
            }
            else
            {
                locN = locN*10 + (src[index]-'0');
            }
        }
        else if('['==src[index])
        {
            sq = 1;
            digit = 0;
        }
        else if(']'==src[index])
        {
            tempStr[sub] = '\0';
            
            if(NULL==dst)
            {
                dst = (char*)malloc(sub*locN);
                accLen =  sub*locN;
                //for(i=0;i<locN;i++)
                //    strcat(dst, tempStr);
                //sub = 0;
            }
            else
            {
                dst = (char*)realloc(dst, sub*locN+accLen);
                accLen += sub*locN;
            }
            for(i=0;i<locN;i++)
                strcat(dst, tempStr);
            sub = 0;
            sq = 0;
            locN=1;
        }
        else
        {
             tempStr[sub++] = src[index];
        }
        index++;
    }
    return dst;
}
char* decode(char*srcStr)
{
    int len = 0, index=0, s1=-1,s2=-1, i=0,j=0,sign=0;
    char *tmp=NULL, *tmpdst=NULL, substr[100]={0};
    len = strlen(srcStr);
    if(NULL==srcStr)
        return NULL;
    
    while(index<len)
    {
        if('['==srcStr[index])
        {
            if(s2<0)
            {
                s2 = index;
            }
            else
            {
                s1 = s2;
                s2 = index;
            }
        }
        if(']'==srcStr[index])
        {
            if(s1>-1)
            {
                sign = 1;
                break;
            }
            else
            {
                tmpdst=decodeStr(srcStr);
                break;
            }
        }
        index++;
        
    }
    if(1==sign)
    {
        tmp = (char*)malloc(index-s1+1);
        for(i=s1+1;i<=index;i++)
            tmp[j++]=srcStr[i];
        tmp[j] = '\0';
        tmpdst=decodeStr(tmp);
                
        free(tmp);
        tmp = (char*)malloc(strlen(tmpdst)+strlen(srcStr)-(index-s1));
        strncpy(tmp, srcStr,s1+1);
        strcat(tmp,tmpdst);
        free(tmpdst);
        j=0;
        for(i=index+1;i<len;i++)
            substr[j++] = srcStr[i];
        strcat(tmp, substr);
        tmpdst=decode(tmp);
        free(tmp);
    }
    return tmpdst;
}
int main()
{
    char src[100] = {0};
    char* dst = NULL;
    gets(src);
    dst = decode(src);
    
    printf("dst: %s\n", dst);
    if(NULL!=dst) 
        free(dst);
    return 0;
}
