/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:58:43 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/18 20:07:00 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include "libft/libft.h"
#define	MAX_LEN 4294967295


int	send_len(char *str, int pid)
{
	int	i;
	size_t	msg_len;

	msg_len = ft_strlen(str);
	if (msg_len > MAX_LEN)
	{
		write(1, "Message too large!\n", 20);
		return (0);
	}
	i = 0;
	while (i < 32)
	{
		kill(pid, SIGUSR1 + (1 & (msg_len >> i)));
		usleep(150);
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	int server_pid;
	char c;
	int i;
	
	if (argc != 3)
		return (0);
	server_pid = ft_atoi(argv[1]);
	if (!send_len(argv[2], server_pid))
		return (0);
	while(*argv[2] != '\0')
	{
		i = 0;
		c = *argv[2];
		while(i < 8)
		{
			usleep(200);
			kill(server_pid, SIGUSR1 + (1 & (c >> i)));
			i++;
		}
		argv[2]++;
	}
}