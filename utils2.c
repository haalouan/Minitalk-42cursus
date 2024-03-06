/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:22:39 by haalouan          #+#    #+#             */
/*   Updated: 2024/01/12 02:25:29 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	check(unsigned char c, int pid_c)
{
	if (c == '\0')
	{
		if (kill(pid_c, SIGUSR1) == -1)
			signalerror();
	}
}

void	ft_bzero(void	*s, size_t n)
{
	char	*p;
	int		i;

	p = s;
	i = 0;
	while (n > 0)
	{
		p[i] = 0;
		i++;
		n--;
	}
}

void	signalerror(void)
{
	ft_putstr_fd("Failed to send signal", 1);
	exit(1);
}
