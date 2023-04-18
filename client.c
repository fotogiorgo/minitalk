/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:58:43 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/16 19:48:11 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include "libft/libft.h"

int main(int arc, char **argv)
{
	int pid;
	int c; // int or char?
	int	msg_len;
	int i;
	
	pid = ft_atoi(argv[1]);
	i = 0;
	msg_len = ft_strlen(argv[2]);
	//printf("str_len: %i\n", msg_len);
	while (msg_len > 0)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		msg_len--;
	}
	kill(pid, SIGUSR2);
	while(*argv[2] != '\0')
	{
		i = 0;
		c = *argv[2];
		while(i < 8)
		{
			usleep(100);
			kill(pid, SIGUSR1 + (1 & (c >> i)));
			//write(1, "L", 1);
			i++;
		}
		//write(1, "\n", 1);
		argv[2]++;
	}
}

/* int main(int arc, char **argv)
{
	int pid;
	int c;
	int	msg_len;
	
	pid = ft_atoi(argv[1]);
	
	msg_len = ft_strlen(argv[2]);
	//printf("str_len: %i\n", msg_len);
	while (msg_len > 0)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		msg_len--;
	}
	kill(pid, SIGUSR2);
	while(*argv[2])
	{
		usleep(100);
		c = (int)*argv[2];
		while(c > 0)
		{
			kill(pid, SIGUSR1);
			usleep(100);
			c--;
		}
		kill(pid, SIGUSR2);
		argv[2]++;
	}
} */