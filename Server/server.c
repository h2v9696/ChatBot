#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "DB_analyst.h"

#define MAXLINE 4096 // max text line length
#define SERV_PORT 3000 // port
#define LISTENQ 16 // maximum number of client connections

int main ()
{
  int listenfd, connfd, n;
  pid_t childpid;
  socklen_t clilen;
  char buff[MAXLINE];
  struct sockaddr_in cliaddr, servaddr;
  
  //Create a socket for the soclet
  //If sockfd<0 there was an error in the creation of the socket
  if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket");
exit(2);
  }
  
  //preparation of the socket address
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);
 
  //bind the socket
  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
  //listen to the socket by creating a connection queue, then wait for clients
  listen (listenfd, LISTENQ);

  printf("%s\n","Server running...waiting for connections.");
 
  for ( ; ; ) {
    clilen = sizeof(cliaddr);
    // accept a connection
    connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
    
    // printf("%s\n","Received request...");
    // Neu la 0 thi la da fork sang process con
    if ((childpid = fork()) == 0) {
      config_DB();
      //printf ("%s\n","Child created for dealing with client requests");
      // close listening socket of child
      close (listenfd);
      while ((n = recv(connfd, buff, MAXLINE, 0)) > 0)  {
	// Nhan buff tu client va gui answer o day
	printf("%s","Tao la ChatBot: ");
	//strcpy(buff, get_reply(buff));
	//puts(buff);
	puts(get_reply(buff));
	send(connfd, get_reply(buff), MAXLINE, 0);
      }
      
      if (n < 0)
	printf("%s\n", "Read error");
      // Handle close client socket, neu tat thi close
      //close(connfd);
      //close_DB();
      exit(0);
    }
    // Dong socket cua server chinh
    close(connfd);
    
  }
}
