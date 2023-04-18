/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:58:45 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/18 20:46:06 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#define INT_MAX 2147483648

/* SIGUSR1 == 30 SIGUSR2 == 31 */

void	get_len(int sig, size_t *msg_len)
{
	static size_t	len = 0;
	static size_t	multipliar = 1;

	len += multipliar * (sig - 30);
	multipliar *= 2;
	if (multipliar > INT_MAX)
	{
		*msg_len = len;
		len = 0;
		multipliar = 1;
	}
}

int	get_msg(char *msg, int sig, int msg_len)
{
	static int	c = 0;
	static int	i = 0;
	static int	multipliar = 1;

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
		i = 0;
		return (1);
	}
	else
		return (0);
}

/* SIGUSR1 is for 0  and SIGUSR1 for 1*/
void	dummy_handler2(int sig)
{
	static char		*msg;
	static size_t	msg_len;
	
	if (msg_len)
	{
		if (msg == NULL)
			msg = malloc(msg_len);
		if (get_msg(msg, sig, msg_len))
		{
			write(1, msg, msg_len);
			write(1, "\n", 1);
			free(msg);
			msg = NULL;
			msg_len = 0;
		}
	}
	else
		get_len(sig, &msg_len);
}

/*	things work fine, except if you do 100 000 chars */
int main(void)
{
	struct sigaction sa;
	
	sa.sa_handler = &dummy_handler2;
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}