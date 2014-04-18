/*
** main.c for Server in /home/chouag_m/rendu/cpp_nibbler
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Sun Apr  6 14:11:26 2014 Mehdi Chouag
** Last update Fri Apr 18 13:20:09 2014 Mehdi Chouag
*/

#include "header.h"

void                    connect_client(char *str)
{
  if (strcmp(str, "1") == 0)
    system("xdotool key Up");
  if (strcmp(str, "2") == 0)
    system("xdotool key Left");
  if (strcmp(str, "3") == 0)
    system("xdotool key Down");
  if (strcmp(str, "4") == 0)
    system("xdotool key Right");
  if (strcmp(str, "6") == 0)
    system("xdotool key Return");
  if (strcmp(str, "5") == 0)
    system("xdotool key s");
}

void                    init_socket(t_server *s)
{
  int			opt;

  opt = 1;
  s->listenfd = xsocket(AF_INET, SOCK_STREAM, 0);
  setsockopt(s->listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  bzero(&(s->servaddr),sizeof(s->servaddr));
  s->servaddr.sin_family = AF_INET;
  s->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  s->servaddr.sin_port = htons(65510);
  xbind(s->listenfd, &(s->servaddr), sizeof(s->servaddr));
  xlisten(s->listenfd, 1024);
}

int		main(void)
{
  t_server	c;

  init_socket(&c);
  while (42)
    {
      c.clilen = sizeof(c.cliaddr);
      c.connfd = xaccept(c.listenfd, &(c.cliaddr), &(c.clilen));
      if ((c.childpid = fork()) == 0)
	{
	  close (c.listenfd);
	  while (42)
	    {
	      c.n = recvfrom(c.connfd, c.mesg, 1000, 0, (struct sockaddr *)&(c.cliaddr), &(c.clilen));
	      sendto(c.connfd, c.mesg, c.n, 0 ,(struct sockaddr *)&(c.cliaddr),sizeof(c.cliaddr));
	      c.mesg[c.n] = '\0';
	      connect_client(c.mesg);
	    }         
	}
      close(c.connfd);
    }
  return (0);
}
