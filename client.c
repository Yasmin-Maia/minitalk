/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:47:53 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 18:18:23 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_msg_received = 0;

static void	ack_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		g_msg_received = 1;
	if (sig == SIGUSR2)
	{
		ft_printf("Message received!\n");
		exit(0);
	}
}

void	send_char(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_msg_received = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
		bit--;
	}
	while (!g_msg_received)
		pause();
}

void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

void	setup_client_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
		error_exit("Usage: ./client <server_pid> <message>");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		error_exit("Invalid PID");
	setup_client_signals();
	send_string(server_pid, argv[2]);
	pause();
	return (0);
}
