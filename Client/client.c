#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main(int argc, char **argv) 
{
  int sockfd;
  struct sockaddr_in servaddr;
  char sendline[MAXLINE], recvline[MAXLINE];
  
  // Co the sua thanh fix cung server
  if (argc !=2) {
    perror("Usage: TCPClient <IP address of the server"); 
    exit(1);
  }
  
  // Create a socket for the client
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket");
    exit(2);
  }
  
  // Tao socket
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr= inet_addr(argv[1]);
  servaddr.sin_port =  htons(SERV_PORT);
	
  // Ket noi den server 
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
    perror("Problem in connecting to the server");
    exit(3);
  }
  // Gui message, them header vao day
  while (fgets(sendline, MAXLINE, stdin) != NULL) {
    // Loai bo Enter
    sendline[strlen(sendline) - 1] = '\0';
    send(sockfd, sendline, strlen(sendline) + 1, 0);

    if (recv(sockfd, recvline, MAXLINE,0) == 0){
      perror("The server terminated prematurely"); 
      exit(4);
    }
    // Thay cai nay bang ten con ChatBot
    printf("%s", "Tao la ChatBot: ");
    fputs(recvline, stdout);
    printf("\n");

  }
  
  exit(0);
}
