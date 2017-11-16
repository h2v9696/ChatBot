#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void finish_with_error();

// thay %s trong query bang xau s
void change_query(char* query,char *s);
//Khoi tao
void config_DB();
// Lay cau tra loi
char* get_reply(char *s);
// Them vao DB
int insert_data(char* mess,char* reply);

void close_DB();
