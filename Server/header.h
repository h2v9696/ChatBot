#include <stdio.h>
#include <string.h>
#include "DB_analyst.h"
#define NUMBER_OF_HEADERS 25

//Gan header
char* bind_header(char* header, char* line);
//Tach header
char* extract_header(char* line);
//Kiem tra header
int check_header(char* header);
//Kiem tra vi tri ngat
int check_cut_position(char* line, char characterToCut);
//Chon phan tu trong param
char* choose(char* param);
//Xu ly cac header la function
char* func_header(char* s);
//Xu ly header
char* header_process(char *s);
