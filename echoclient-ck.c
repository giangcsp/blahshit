/*
* echoclient.c - An echo client
*/
#include "csapp.h"

int main(int argc, char **argv) 
 {
  int clientfd, port;
  char *host, buf[MAXLINE];
  rio_t rio;
  int fd;
  char buff[MAXLINE];

  if (argc != 3) 
   {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
   }
  host = argv[1];
  port = atoi(argv[2]);

  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd);
  
  

  while (1) 
   {
    int size, n;
    printf("Enter file name: ");
    if (Fgets(buf, MAXLINE, stdin) == NULL) break;
    buf[strlen(buf)-1] = 0;
    printf("\nSave to: ");
    Fgets(buff, MAXLINE, stdin);
    fd = open(buff, O_CREAT | O_TRUNC | O_WRONLY);
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readlineb(&rio, buf, MAXLINE);
    size = atoi(buf);
    int counter = 0;
    while (counter < size){
        n = Rio_readlineb(&rio, buf, MAXLINE);
        Rio_writen(fd, buf, n);
        counter += 1;
    }
   }
  Close(clientfd);
  exit(0);
 }
