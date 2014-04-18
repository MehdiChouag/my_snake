/*
** header.h for header in /home/chouag_m/Manette
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Thu Apr  3 17:17:20 2014 Mehdi Chouag
** Last update Fri Apr  4 22:54:06 2014 Mehdi Chouag
*/

#ifndef HEADER_HH_
# define HEADER_HH_

# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <netdb.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

#define NB_CLIENT 10
#define PROTOCOL "TCP"

typedef struct          s_server
{
  int			listenfd;
  int			connfd;
  int		        n;
  socklen_t		clilen;
  pid_t			childpid;
  char			mesg[1000];
  struct sockaddr_in	servaddr;
  struct sockaddr_in    cliaddr;
}                       t_server;

int                     xbind(int sockfd, struct sockaddr_in *addr, socklen_t addrlen);
int                     xsocket(int domain, int type, int protocol);
int                     xconnect(int sockfd, struct sockaddr_in *addr, socklen_t addrlen);
int                     xaccept(int sockfd, struct sockaddr_in *addr ,socklen_t *len);
int                     xlisten(int sockfd, int backlog);
void                    init_socket(t_server *s);
/* void                    init_client(t_client *c, char *ip); */

#endif /* !HEADER_HH_ */
