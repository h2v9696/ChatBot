#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
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

//Kiem tra message co ton tai khong


void config_DB()
{
  con = mysql_init(NULL);
  if (con == NULL)
    {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
    }
  if (mysql_real_connect(con, "localhost", "root", "vietvip96",
			 "BotChat", 0, NULL,  0) == NULL)
    {
      finish_with_error(con);
    }
}

char* get_reply(char *s)
{
  //de tam mac dinh tra loi (hard code) cho cau hoi khong biet
  //co the sua de chon 1 cau tra loi trong so set cau tra loi mac dinh cho cau hoi khong tim thay
  char S_query[MAXLEN] = "SELECT IFNULL( (SELECT R.Reply FROM Message AS M, Relationship AS Re, Reply AS R WHERE M.Mcode = Re.Mcode AND Re.Rcode = R.Rcode AND M.Mess LIKE '%%s%' ORDER BY RAND() LIMIT 1) , 'Cant you teach me how to answer that? <3')";
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

//insert mess va reply da co
int insert_data(char* mess,char* reply)
{
  char
    I_query_mess[MAXLEN] = "INSERT INTO Message (mess)  SELECT  \"%s\" AS tmp WHERE NOT EXISTS ( SELECT mess FROM Message WHERE mess = \"%s\") LIMIT 1;",
    I_query_mess_set[MAXLEN] = "SELECT Mcode INTO @Mcode FROM Message WHERE mess = \"%s\";",
    I_query_reply[MAXLEN] = "INSERT IGNORE INTO Reply (reply)  SELECT \"%s\" AS tmp WHERE NOT EXISTS ( SELECT reply FROM Reply WHERE reply = \"%s\") LIMIT 1;",
    I_query_reply_set[MAXLEN] = "SELECT  Rcode INTO  @Rcode FROM Reply  WHERE reply = \"%s\";",
    I_query_relationship[MAXLEN] = "INSERT INTO Relationship (Mcode,Rcode) SELECT * FROM(SELECT @Mcode, @Rcode) AS tmp WHERE NOT EXISTS ( SELECT Mcode,Rcode FROM Relationship WHERE Mcode = @Mcode AND Rcode =@Rcode ) LIMIT 1;";
    //int r=0;
     if (mysql_query(con,"ALTER TABLE Message AUTO_INCREMENT = 1;"))
    {
      finish_with_error(con);
    }
  if (mysql_query(con,"ALTER TABLE Reply AUTO_INCREMENT = 1;"))
    {
      finish_with_error(con);
    }
  change_query(I_query_mess,mess);
  change_query(I_query_mess_set,mess);
  change_query(I_query_reply,reply);
  change_query(I_query_reply_set,reply);
  if (mysql_query(con, I_query_mess))
    {
      finish_with_error(con);
      return 1;
    }
  if (mysql_query(con, I_query_mess_set))
    {
      finish_with_error(con);
      return 1;
      }
  if (mysql_query(con, I_query_reply))
    {
      finish_with_error(con);
      return 1;
    }
  if (mysql_query(con, I_query_reply_set))
    {
      finish_with_error(con);
      return 1;
    }
    if (mysql_query(con, I_query_relationship))
    {
      finish_with_error(con);
      return 1;
      }
  return 0;
}

void close_DB()
{
  mysql_close(con);
  exit(0);
}

