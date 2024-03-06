/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:15:08 by haalouan          #+#    #+#             */
/*   Updated: 2024/01/12 02:30:14 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_condition;

void	reset_all(char tab[], int *i, unsigned char *c)
{
	ft_bzero(tab, 4);
	*i = 0;
	*c = 0;
	g_condition = 0;
}

static int	count_size_bytes(unsigned char c)
{
	int	size_byte;

	size_byte = 0;
	if (c < 192)
		size_byte = 1;
	else if (c >= 192 && c < 224)
		size_byte = 2;
	else if (c >= 224 && c < 240)
		size_byte = 3;
	else if (c >= 240)
		size_byte = 4;
	return (size_byte);
}

void	print_value(char tab[], unsigned char *c, int *i)
{
	static int	size_bytes;

	if (g_condition == 0)
		size_bytes = count_size_bytes(*c);
	g_condition = 1;
	if (*i < size_bytes)
		tab[(*i)++] = *c;
	if (*i == size_bytes)
	{
		ft_putstr_fd(tab, 1);
		reset_all(tab, i, c);
	}
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				count = 0;
	static pid_t			pid_c;
	static int				i = 0;
	static char				tab[4];

	(void)context;
	if (pid_c == 0)
		pid_c = info->si_pid;
	else if (pid_c != info->si_pid)
	{
		pid_c = info->si_pid;
		reset_all(tab, &i, &c);
		count = 0;
	}
	c = (c << 1) + (signal == SIGUSR1);
	if (++count == 8)
	{
		check(c, pid_c);
		print_value(tab, &c, &i);
		c = 0;
		count = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sigg;

	sigg.sa_sigaction = &signal_handler;
	sigg.sa_flags = SA_SIGINFO;
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
