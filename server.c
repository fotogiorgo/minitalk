/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:58:45 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/18 10:08:19 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

//sig1 == 30 sig2 == 31

char *msg;

int	handler(int sig)
{
	static int	msg_len = 0;
	//static int	reset = 0;

	if (sig == 30)
		msg_len++;
	if (sig == 31)
	{
		//printf("str_len: %i\n", msg_len);
		msg = malloc(msg_len + 1);
		//reset = 1;
	}
	return (msg_len);
}

/* void	handler2(int sig)
{
	const int	msg_len = handler(0);
	static int	c = 0;
	static int	i = 0;
	
	if (sig == 31)
	{
		msg[i] = c;
		i++;
		c = 0;
		if (i == msg_len)
		{
			msg[i] = '\0';
			write(1, msg, msg_len);
		}
	}
	else
		c++;	
} */

void	dummy_handler2(int sig)
{
	const int	msg_len = handler(0);
	static int	c = 0;
	static int	i = 0;
	static int	multipliar = 1;
	
	//printf("str_len: %i\n", msg_len);
	if (multipliar <= 128)
	{
		// so sig1 is for 0
		c += multipliar * (sig - 30);
		multipliar *= 2;
	}
	if (multipliar == 256)
	{
		msg[i] = c;
		i++;
		c = 0;
		multipliar = 1;
	}
	if (i == msg_len)
	{
		msg[i] = '\0';
		write(1, msg, msg_len);
		write(1, "\n", 1);
		free(msg);
		i = 0;
		msg = NULL;
		//send sig to client for confirmation
	}
}


/* dummy handler works, i only have to change my main so it gets 
a msg second time in a row, cnd check my free's malloc guards, etc */

/* i did the double calling but handlers keeps the msg_len and things fck up */

int main(void)
{
	struct sigaction sa;
	//sa.sa_handler = (void (*)(int))&handler;
	printf("%i\n", getpid());
/* 	while (msg == 0)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	sa.sa_handler = &dummy_handler2;
	//write(1, "msg_len received\n", 18); */
	while (1)
	{
		if (msg == NULL)
			sa.sa_handler = (void (*)(int))&handler;
		else
			sa.sa_handler = &dummy_handler2;
			
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}