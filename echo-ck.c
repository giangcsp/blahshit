/*
* echo - read and echo text lines until client closes connection
*/
#include "csapp.h"

void echo(int connfd) 
 {
  size_t n;
  char buf[MAXLINE];
  rio_t rio, frio;
  int fd;
  char buff[MAXLINE];
  Rio_readinitb(&rio, connfd);
  while(1) 
   {
      Rio_readlineb(&rio, buf, MAXLINE);
      printf("\n'%s'\n", buf);
      fd = Open(buf, O_RDONLY, 0);
      Rio_readinitb(&frio, fd);
      n = 0;
      while (Rio_readlineb(&frio, buff, MAXLINE)) n += 1;
      sprintf(buff, "%ld", n);
      Rio_writen(connfd, buff, strlen(buff));
      lseek(fd, 0, SEEK_SET);

      while ((n = Rio_readlineb(&frio, buff, MAXLINE)) != 0){
        printf("blah");
        Rio_writen(connfd, buff, n);
      }
   }
 }

