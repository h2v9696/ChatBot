#include "header.h"
#include <time.h>
#define MAX_PARAM 10
#include <stdio.h>

char* bind_header(char* header, char* line)
{
    char *bindedHeader = (char *) malloc (256 * sizeof(char));
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
    char *extractedHeader = (char *) malloc (25 * sizeof(char));
    do {
        extractedHeader[i] = line[i];
        i++;
    } while((line[i] != ' ' && line[i] !='\0') && i <= 25);
    extractedHeader[i] = '\0';
    return extractedHeader;
}

int check_cut_position(char* line, char characterToCut)
{
    int i=0;
    int length = strlen(line);
    while(i < length)
    {
        if(line[i] == characterToCut) return i;
	i++;
    }
    return -1;
}

char* choose(char* param) {
  char* temp;
  char* list_param[MAX_PARAM];
  int i = 1;
  //printf("1%s\n%s\n", temp, param);
  srand((unsigned) time(NULL));
  temp = strtok (param, ",");
  //printf("%s\n", temp);
  list_param[0] = (char*) malloc (256 * sizeof(char));
  strcpy(list_param[0], temp);
  // printf("%s\n", temp);
  while (temp != NULL)
  {
    //printf("%s\n", temp);
    list_param[i] = (char*) malloc (256 * sizeof(char));
    strcpy(list_param[i], temp);
    i++;
    temp = strtok (NULL, ",");
  }
  if (i > MAX_PARAM) return "Vuot qua so tham so cho phep!";
  int choosed = rand() % i;
  //printf("%d::%d\n", choosed, i);
  return list_param[choosed];
}

char* choose_emo(char* param) {
  //printf("%s\n", param);
  char* temp = (char*) malloc(256 * sizeof(char));
  if (strcmp(param, "smile") == 0) {
    //printf("%s\n", param);
    //printf("%s\n",choose("(((o(*ﾟ▽ﾟ*)o))),Ｏ(≧∇≦)Ｏ,o(≧∇≦o),(/^▽^)/,⁽(◍˃̵͈̑ᴗ˂̵͈̑)⁽,ヾ（〃＾∇＾）ﾉ♪"));
    strcpy(temp, "(((o(*ﾟ▽ﾟ*)o))),Ｏ(≧∇≦)Ｏ,o(≧∇≦o),(/^▽^)/,⁽(◍˃̵͈̑ᴗ˂̵͈̑)⁽,ヾ（〃＾∇＾）ﾉ♪");
    return choose(temp);
  }
  if (strcmp(param, "sad") == 0) {
    strcpy(temp, "( ≧Д≦),(▰˘︹˘▰),ヽ(●ﾟ´Д｀ﾟ●)ﾉﾟ,(｡•́︿•̀｡),(๑´╹‸╹`๑),(｡-人-｡)");
    return choose(temp);
  } 
  if (strcmp(param, "angry") == 0) {
    strcpy(temp, "凸ಠ益ಠ)凸,( ︶︿︶)_╭∩╮,t(- n -)t,(҂⌣̀_⌣́),(╬ Ò ‸ Ó),（｀Δ´）！");
    return choose(temp);
  }
  return "Wrong emo please type -le for list emo!";
}


char* func_header(char* s) {
  char* func;
  char* param;
  func = extract_header(s);
  param = s + strlen(func) + 1;
  param[strlen(param)] = '\0';
  if (strcmp(func, "-help") == 0) {
    return "\nList of function:\n-help -> Get all functions.\n-infor -> Get information of me.\n-choose <param1>,<param2>,... -> Choose 1 random param from params.\n-le -> Show list emo base on param.\n-emo <param> -> Get emo from server.";
  } else 
    if (strcmp(func, "-infor") == 0) {
      return "I'm ChatBot made by Group5!";
    } else
      if ((strcmp(func, "-choose") == 0) && (param[0] != '\0')) {
	return choose(param);
      } else 
	if ((strcmp(func, "-le") == 0)) {
	  return "List emo: smile, sad, angry";
	} else 
	  if ((strcmp(func, "-emo") == 0) && (param[0] != '\0')) {
	    return choose_emo(param);
	  }
  return "Wrong function syntax, please type -help for all functions syntax";
}

char* header_process(char *s) {
  char* header = (char *) malloc (25 * sizeof(char));
  char* mess;
  char* rep;
  char* temp;
  char* func;
  int pos;
  header = extract_header(s);

  if (strcmp(header, "MESS") == 0) {
    //printf("Dang Add...%s.\n", header);  
    return get_reply(s + strlen(header) + 1);
  }  	
  //printf("Dang Add...%s.\n",header);
  if (strcmp(header, "ADD") == 0) {
    mess = s + strlen(header) + 1;
    pos = check_cut_position(mess, '\\');
    rep = mess + pos + 1;
    mess[pos] = '\0';
    if (insert_data(mess, rep)) {
      return "Da xay ra loi khong them cach tra loi duoc!";
    } else {
      return "Da them cach tra loi cho Bot, cam on ban!";		
    }
  }

  if (strcmp(header, "FUNC") == 0) {
    temp = s + strlen(header) + 1;

    return func_header(temp);
  }
  return "OK";
}
