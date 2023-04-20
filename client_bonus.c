/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:58:43 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/20 18:02:47 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include "libft/libft.h"
#define MAX_LEN 4294967295

int	send_len(char *str, int pid)
{
	int		i;
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
		usleep(50);
		i++;
	}
	return (1);
}

void	wait_confirmation(int sig)
{
	write(1, "\033[0;32m", 8);
	write(1, "Message sent!\n", 15);
	exit(1);
}

void	send_msg(char *str, int server_pid)
{
	int	i;
	int	c;

	while (*str != '\0')
	{
		i = 0;
		c = *str;
		while (i < 8)
		{
			usleep(50);
			kill(server_pid, SIGUSR1 + (1 & (c >> i)));
			i++;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sa;

	if (argc != 3)
		return (0);
	sa.sa_handler = &wait_confirmation;
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	if (!send_len(argv[2], server_pid))
		return (0);
	send_msg(argv[2], server_pid);
	while (1)
		pause();
}
