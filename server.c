/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:58:45 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/18 11:50:43 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#define INT_MAX 2147483648

/* SIGUSR1 == 30 SIGUSR2 == 31 */

unsigned int	msg_len;

void	get_len(int sig)
{
	static size_t	len = 0;
	static size_t	multipliar = 1;

	len += multipliar * (sig - 30);
	multipliar *= 2;
	if (multipliar > INT_MAX)
	{
		msg_len = len;
		len = 0;
		multipliar = 1;
	}
}

/* SIGUSR1 is for 0  and SIGUSR1 for 1*/
void	dummy_handler2(int sig)
{
	static char	*msg;
	static int	c = 0;
	static int	i = 0;
	static int	multipliar = 1;
	
	if (msg == NULL)
		msg = malloc(msg_len);
	if (multipliar <= 128)
	{
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
		write(1, msg, msg_len);
		write(1, "\n", 1);
		free(msg);
		i = 0;
		msg = NULL;
		msg_len = 0;
		//send sig to client for confirmation
	}
}

int main(void)
{
	struct sigaction sa;
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
	{
		if (msg_len == 0)
			sa.sa_handler = &get_len;
		else
			sa.sa_handler = &dummy_handler2;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}