#include <stdio.h>
#include <string.h>
#define NUMBER_OF_HEADERS 25

//Gan header
char* bind_header(char* header, char* line);
//Tach header
char* extract_header(char* line);
//Kiem tra header
int check_header(char* header);
//Kiem tra vi tri ngat
int check_cut_position(char* line, char characterToCut);
//
char* header_process(char *s);
