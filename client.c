/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:47:53 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 23:45:05 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_msg_received = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		g_msg_received = 1;
		ft_printf("Message received!\n");
	}
	else if (sig == SIGUSR1)
		g_msg_received = 1;
}

void	send_char(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		signal(SIGUSR1, ack_handler);
		signal(SIGUSR2, ack_handler);
		g_msg_received = 0;
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(ft_printf("Failed to send signal to %d\n", pid));
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(ft_printf("Failed to send signal to %d\n", pid));
		}
		bit--;
		while (g_msg_received == 0)
			pause();
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		server_pid;
	char	*str;

	if (argc != 3)
	{
		ft_printf("Usage: ./client <server_pid> <message>");
		return (1);
	}
	i = 0;
	server_pid = ft_atoi(argv[1]);
	str = argv[2];
	if (server_pid <= 0)
	{
		ft_printf("Invalid PID");
		return (1);
	}
	while (str[i] != '\0')
		send_char(server_pid, str[i++]);
	send_char(server_pid, '\0');
	while (g_msg_received == 0)
		pause();
	return (0);
}
