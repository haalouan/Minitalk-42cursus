/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:50:21 by haalouan          #+#    #+#             */
/*   Updated: 2024/01/12 01:21:36 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				count;
	static pid_t			pid_c;

	(void)context;
	if (pid_c == 0)
		pid_c = info->si_pid;
	else if (pid_c != info->si_pid)
	{
		pid_c = info->si_pid;
		count = 0;
		c = 0;
	}
	if (signal == SIGUSR1)
		c = (c << 1) | 1;
	else if (signal == SIGUSR2)
		c = (c << 1) | 0;
	count++;
	if (count == 8)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		count = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sigg;

	sigg.sa_flags = SA_SIGINFO;
	sigg.sa_sigaction = &signal_handler;
	pid = getpid();
	ft_putstr_fd("pid :", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	if (sigaction(SIGUSR1, &sigg, NULL) == -1)
		ft_putstr_fd("Error", 1);
	if (sigaction(SIGUSR2, &sigg, NULL) == -1)
		ft_putstr_fd("Error", 1);
	while (1)
		pause();
	return (0);
}
