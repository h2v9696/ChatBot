#include <stdio.h>
#include <string.h>
#include "header.h"

char HEADERS[NUMBER_OF_HEADERS][25] = {
    "CHOOSE",
    "ADD"
};

char* bind_header(char* header, char* line)
{
    char *bindedHeader;
    if(line != NULL)
    {
        strcpy (bindedHeader, header);
        strcat (bindedHeader, " ");
        strcat (bindedHeader, line);
        return bindedHeader;
    }
    else
    {
        return NULL;
    }
}

char* extract_header(char* line)
{
    int i = 0;
    char *extractedHeader;
    do {
        extractedHeader[i] = line[i];
        i++;
    } while(line[i] != ' ' && i <= 25);
    return extractedHeader;
}

int check_header(char* header)
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

int check_cut_position(char* line, char characterToCut)
{
    int i=0;
    int length = strlen(line);
    while(i < length)
    {
        if(line[i] == characterToCut) return i;
    }
    return -1;
}

/*void main ()
{
    char line[256];
    char final[256];
    char exHeader[25];
    int isHeader;
    int count;
    strcpy(line, "cat, dogs ");
    strcpy(final, bindHeader(HEADERS[0],line));
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
}*/
