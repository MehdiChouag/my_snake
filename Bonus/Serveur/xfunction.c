/*
** xfunction.c for xfunction in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Mar 26 18:15:05 2014 Mehdi Chouag
** Last update Sat Mar 29 18:32:39 2014 Mehdi Chouag
*/

#include "header.h"

int	xbind(int sockfd, struct sockaddr_in *addr, socklen_t addrlen)
{
  int	rbind;

  rbind = bind(sockfd, (const struct sockaddr *)addr, addrlen);
  if (rbind == -1)
    {
      perror("Bind ");
      close(sockfd);
      exit(EXIT_FAILURE);
    }
  return (rbind);
}

int	xsocket(int domain, int type, int protocol)
{
  int	fd;

  fd = socket(domain, type, protocol);
  if (fd == -1)
    {
      perror("Socket ");
      exit(EXIT_FAILURE);
    }
  return (fd);
}

int	xaccept(int sockfd, struct sockaddr_in *addr ,socklen_t *len)
{
  int	ret;

  ret = accept(sockfd, (struct sockaddr *)addr, len);
  if (ret == -1)
    {
      perror("Accept ");
      exit(EXIT_FAILURE);
    }
  return (ret);
}

int	xlisten(int sockfd, int backlog)
{
  int	ret;

  ret = listen(sockfd, backlog);
  if (ret == -1)
    {
      perror("Listen ");
      exit(EXIT_FAILURE);
    }
  return (ret);
}

int	xconnect(int sockfd, struct sockaddr_in *addr, socklen_t addrlen)
{
  int	ret;

  ret = connect(sockfd, (const struct sockaddr *)addr, addrlen);
    if (ret == -1)
    {
      perror("Connect ");
      exit(EXIT_FAILURE);
    }
  return (ret);
}
