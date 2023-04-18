/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:36:54 by jofoto            #+#    #+#             */
/*   Updated: 2023/03/29 20:30:16 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	while (*s != 0)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}