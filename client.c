/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:47:53 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 00:02:47 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Message received!\n", 18);
		exit(0);
	}
	(void)sig;
}

static void	timeout_handler(int sig)
{
	(void)sig;
	write(2, "Timeout: No response from server\n", 33);
	exit(1);
}

void	send_char(pid_t pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(5000);
		bit--;
	}
}

void	send_string(pid_t pid, char *str)
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

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		error_exit("Usage: ./client <server_pid> <message>");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		error_exit("Invalid PID");
	signal(SIGUSR1, ack_handler);
	signal(SIGUSR2, ack_handler);
	signal(SIGALRM, timeout_handler);
	alarm(30);
	send_string(server_pid, argv[2]);
	pause();
	return (0);
}
