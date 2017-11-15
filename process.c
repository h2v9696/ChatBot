#include <stdio.h>
#include <string.h>
#include "header.h"

char* BlindHeader (char* header, char* line)
{
    char blindedHeader[256];
    if(line != NULL)
    {
        strcpy (blindedHeader, header);
        strcat (blindedHeader, " ");
        strcat (blindedHeader, line);
        return blindedHeader;
    }
    else
    {
        return NULL;
    }
}

char* ExtractHeader(char* line)
{
    int i=0;
    char extractedHeader[25];
    do{
        extractedHeader[i] = line[i];
        i++;
    }while(line[i] != ' ' && i <= 25);
    return extractedHeader;
}

int CheckHeader(char* header)
{
    int i = 0;
    //check header with every existed headers
    while(i < NUMBER_OF_HEADERS)
    {
        int length;
        int j = 0;
        length = strlen(HEADERS[i]);
        //check every char from start of header with HEADERS's char
        while(j < length)
        {
            if(HEADERS[i][j] != header[j])
            {
                //if different, break
                break;
            }
            j++;
        }
        // if j == length, its mean this header existed
        if(j == length) return 1;
        i++;
    }
    //if loop done, its mean no HEADER equal with header
    return 0;
}

int CheckCutPosition(char* line, char characterToCut )
{
    int i=0;
    int length = strlen(line);
    while(i < length)
    {
        if(line[i] == characterToCut) return i;
    }
    return -1;
}

void main ()
{
    char line[256];
    char final[256];
    char exHeader[25];
    int isHeader;
    int count;
    strcpy(line, "cat, dogs ");
    strcpy(final, BlindHeader(HEADERS[0],line));
    strcpy(exHeader, ExtractHeader(final));
    isHeader = CheckHeader(exHeader);
    printf("%s\n",final);
    printf("%s\n",exHeader);
    if(isHeader == 1)
    {
        printf ("This is an existed header\n");
    }
    else
    {
        printf("This isnt an existed header\n");
    }
}