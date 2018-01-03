#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <gtk/gtk.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 8080 /*port*/

//tach ho ra lam cai thu vien :v eo biet lam makefile nen de vao day de chay
GtkWidget *g_tey_mess;
GtkWidget *g_tbf_mess;
GtkWidget *g_tey_mess_add;
GtkWidget *g_tey_reply_add;
GtkWidget *g_dag_add;
int sockfd;
char sendline[MAXLINE], recvline[MAXLINE];

char* get_Recv() {
  char receive_buffer[MAXLINE];
      int received_bytes = 0;
      int remaining_bytes = sizeof(receive_buffer);
      int res;
      memset(receive_buffer, 0 , strlen(receive_buffer));

      while (remaining_bytes > 0) {
	//Fix loi o client khac nhan duoc recv khong mong muon
	/*if (received_bytes == res) {
	  memset(receive_buffer, 0 , strlen(receive_buffer));
	  res = recv(sockfd , receive_buffer , remaining_bytes, 0);
	  //printf("0 Recv:%s\nRes:%d Remain:%d Received:%d\n", receive_buffer, res, remaining_bytes,received_bytes);

	  } else*/
	  res = recv(sockfd , &receive_buffer[received_bytes] , remaining_bytes, 0);
	//printf("1 Recv:%s\nRes:%d Remain:%d Received:%d\n", receive_buffer, res, remaining_bytes,received_bytes);
        //if (recv(sockfd , receive_buffer , remaining_bytes, 0) == 0) {
        if (res <= 0){ 
	  perror("The server terminated prematurely"); 
	  exit(4);
        }
        received_bytes += res;
        remaining_bytes -= res;
	//printf("2 Recv:%s\nRes:%d Remain:%d Received:%d\n", receive_buffer, res, remaining_bytes,received_bytes);
	//if (received_bytes >= strlen(receive_buffer)) break;
	
      }
      return receive_buffer;
}

// called when button send is clicked sua tham so de truyen vao
char* bind_header(char* header, char* line)
{
  char *bindedHeader = (char *) malloc (MAXLINE * sizeof(char));
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
//khi nhan enter thi hien mess
void on_tey_mess_activate()
{
  GtkTextIter iter;
  char tmp[256];
  
  const gchar *mess = gtk_entry_get_text(GTK_ENTRY(g_tey_mess));
  if (mess[0] != '\0')
    {
      gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(g_tbf_mess),&iter,0);
      gtk_text_buffer_insert(GTK_TEXT_BUFFER(g_tbf_mess),&iter,strcat(bind_header("Toi:", mess),"\n"),-1);
      
      strcpy(sendline,"\0");
      strcpy(sendline,mess);
      gtk_entry_set_text(GTK_ENTRY(g_tey_mess),"");
 
      // Gui mess
      if (sendline[0] == '-') {
	strcpy (sendline, bind_header("FUNC", sendline));
      } else {
	strcpy (sendline, bind_header("MESS", sendline));
      }
      
      send(sockfd, sendline, strlen(sendline) + 1, 0);
      
      /*char receive_buffer[MAXLINE];
      int received_bytes = 0;
      int remaining_bytes = sizeof(receive_buffer);
      int res;
      memset(receive_buffer, 0 , strlen(receive_buffer));

      while (remaining_bytes > 0) {
	//Fix loi o client khac nhan duoc recv khong mong muon
	/*if (received_bytes == res) {
	  memset(receive_buffer, 0 , strlen(receive_buffer));
	  res = recv(sockfd , receive_buffer , remaining_bytes, 0);
	  //printf("0 Recv:%s\nRes:%d Remain:%d Received:%d\n", receive_buffer, res, remaining_bytes,received_bytes);

	  } else
	  res = recv(sockfd , &receive_buffer[received_bytes] , remaining_bytes, 0);
	//printf("1 Recv:%s\nRes:%d Remain:%d Received:%d\n", receive_buffer, res, remaining_bytes,received_bytes);
        //if (recv(sockfd , receive_buffer , remaining_bytes, 0) == 0) {
        if (res <= 0){ 
	  perror("The server terminated prematurely"); 
	  exit(4);
        }
        received_bytes += res;
        remaining_bytes -= res;
	//printf("2 Recv:%s\nRes:%d Remain:%d Received:%d\n", receive_buffer, res, remaining_bytes,received_bytes);
	//if (received_bytes >= strlen(receive_buffer)) break;
	
      }*/
      //printf("%d\n", recv(sockfd , &receive_buffer[received_bytes] , remaining_bytes, 0));
      gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(g_tbf_mess),&iter,0);
      gtk_text_buffer_insert(GTK_TEXT_BUFFER(g_tbf_mess),&iter,strcat(bind_header("CuteBot:", get_Recv()),"\n"),-1);
    } else {
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(g_tbf_mess),&iter,0);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(g_tbf_mess),&iter,"Hay nhap gi do!\n",-1);
  }
}

//khi nhan add thi hien dialog
void on_btn_add_clicked()
{
  gtk_widget_show(g_dag_add);
  gtk_entry_set_text(GTK_ENTRY(g_tey_mess_add),"");
  gtk_entry_set_text(GTK_ENTRY(g_tey_reply_add),"");  
  gint result = gtk_dialog_run(GTK_DIALOG (g_dag_add));
  switch (result)
    {
    case GTK_RESPONSE_ACCEPT:
      printf("OK\n");
      break;
    default:
      printf("CANCEL\n");
      break;
    }
  gtk_widget_hide (g_dag_add);
}

//khi nhan dong add dialog
on_btn_cancel_clicked()
{
  //const gchar *mess = gtk_entry_get_text(GTK_ENTRY(g_tey_mess_add));
  
  //printf("%s\n",mess);
  gtk_entry_set_text(GTK_ENTRY(g_tey_mess_add),"");
  gtk_entry_set_text(GTK_ENTRY(g_tey_reply_add),"");
  gtk_dialog_response (GTK_DIALOG (g_dag_add), GTK_RESPONSE_NONE);

  //gtk_widget_destroy(g_dag_add);
}

on_btn_ok_clicked()
{
  GtkTextIter iter;
  const gchar *mess = gtk_entry_get_text(GTK_ENTRY(g_tey_mess_add));
  const gchar *reply = gtk_entry_get_text(GTK_ENTRY(g_tey_reply_add));
  if (strstr(mess,"\\") == NULL && strstr(reply, "\\") == NULL) {
  gtk_dialog_response (GTK_DIALOG (g_dag_add), GTK_RESPONSE_ACCEPT);
  strcpy(sendline,"\0");
  strcpy(sendline,mess);
  strcat(sendline,"\\");
  strcat(sendline,reply);
  strcpy (sendline, bind_header("ADD", sendline));
  send(sockfd, sendline, strlen(sendline) + 1, 0);
  /*if (recv(sockfd, recvline, MAXLINE,0) == 0){
    perror("The server terminated prematurely"); 
    exit(4);
    }*/

  gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(g_tbf_mess),&iter,0);
  gtk_text_buffer_insert(GTK_TEXT_BUFFER(g_tbf_mess),&iter,strcat(bind_header("CuteBot:", get_Recv()),"\n"),-1);
  
  gtk_entry_set_text(GTK_ENTRY(g_tey_mess_add),"");
  gtk_entry_set_text(GTK_ENTRY(g_tey_reply_add),"");
  gtk_dialog_response (GTK_DIALOG (g_dag_add), GTK_RESPONSE_ACCEPT);
  
  } else {
    printf("Khong duoc nhap slash!\n");
  }  //gtk_widget_destroy(g_dag_add);
}


// khi co reply thi hien len
void on_reply_activate(char *reply)
{
  gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(g_tbf_mess),"\n",1);
  gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(g_tbf_mess),(const gchar*)reply,-1);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

int main(int argc, char **argv) 
{
  struct sockaddr_in servaddr;
  
  
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
  servaddr.sin_port = htons(SERV_PORT);
	
  // Ket noi den server 
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
    perror("Problem in connecting to the server");
    exit(3);
  }
  //gtk config
  GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "chatui.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    // get pointers
    g_tbf_mess = GTK_WIDGET(gtk_builder_get_object(builder, "tbf_mess"));
    g_tey_mess = GTK_WIDGET(gtk_builder_get_object(builder, "tey_mess"));
    g_dag_add = GTK_WIDGET(gtk_builder_get_object(builder, "dag_add"));
    g_tey_mess_add = GTK_WIDGET(gtk_builder_get_object(builder, "tey_mess_add"));
    g_tey_reply_add = GTK_WIDGET(gtk_builder_get_object(builder, "tey_reply_add"));
    
    //gtk_dialog_response (Gg_dag,gint response_id);
   	
    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();
  // Gui message, them header vao day

  /*while (fgets(sendline, MAXLINE, stdin) != NULL) {
    //Xu ly neu client go lenh chuc nang (-help, -choose, -infor)
    
    // Loai bo Enter
    sendline[strlen(sendline) - 1] = '\0';
    if (strstr(sendline, "\\") == NULL) {

      // Gui mess
      if (sendline[0] == '-') {
	strcpy (sendline, bind_header("FUNC", sendline));
      } else {
	strcpy (sendline, bind_header("MESS", sendline));
      }


      send(sockfd, sendline, strlen(sendline) + 1, 0);
    
      // strcpy (sendline, bind_header("ADD", sendline));
      // send(sockfd, sendline, strlen(sendline) + 1, 0);
      if (recv(sockfd, recvline, MAXLINE,0) == 0){
	perror("The server terminated prematurely"); 
	exit(4);
      }
      // Thay cai nay bang ten con ChatBot
      printf("%s", "Tao la ChatBot: ");
      fputs(recvline, stdout);
      printf("\n");
    } else {
      //Thong bao khong nhap dau slash
      printf("Khong nhap duoc slash!");
    }

  }*/
  
  exit(0);

}
