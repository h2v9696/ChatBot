#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "DB_analyst.h"
#define MAXLEN 256

MYSQL *con;
void finish_with_error()
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

// thay %s trong query bang xau s
void change_query(char* query,char *s){
  int i;
  char tmp[MAXLEN];
  for(i=0;i<strlen(query);i++)
    {
      if(query[i]=='%'&&query[i+1]=='s')
	{
	  query[i]='\0';
	  strcpy(tmp,query+i+2);
	  strcat(query,s);
	  strcat(query,tmp);
	}
    }
}

void config_DB()
{
  con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);	
  }  
  if (mysql_real_connect(con, "localhost", "root", "vietvip96", 
          "BotChat", 0, NULL, 0) == NULL) 
    {
      finish_with_error(con);
    }
 }

char* get_reply(char *s)
{
  //char *reply;
  char S_query[MAXLEN] = "SELECT R.Reply From Message AS M, Relationship AS Re, Reply AS R WHERE M.Mcode = Re.Mcode AND Re.Rcode = R.Rcode And M.Mess LIKE '%%s%'";
  int r=0;
  change_query(S_query,s);
  if (mysql_query(con, S_query)) 
    {
      finish_with_error(con);
    }
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  row = mysql_fetch_row(result); 
  mysql_free_result(result);
  return row[0];
 }
 void close_DB()
{
  mysql_close(con);
  exit(0);
}
