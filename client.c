/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:30:40 by haalouan          #+#    #+#             */
/*   Updated: 2024/01/12 22:42:13 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_message(unsigned char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				signalerror();
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				signalerror();
				exit(1);
			}
		}
		usleep(500);
		i--;
	}
}

static int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (0);
		i++;
	}
	return (1);
}

int	main(int arc, char **arv)
{
	char	*message;
	int		pid;
	int		i;

	i = 0;
	if (arc == 3 && arv[1][0] != '0')
	{
		if (check_digit(arv[1]) == 0)
		{
			ft_putstr_fd("invalid pid", 1);
			exit(1);
		}
		pid = ft_atoi(arv[1]);
		message = arv[2];
		while (message[i] != '\0')
		{
			send_message(message[i], pid);
			i++;
		}
	}
	else
		ft_putstr_fd("Error:\n<./client> <pid> <string>", 1);
}
