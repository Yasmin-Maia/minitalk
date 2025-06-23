/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:51:05 by ymaia-do          #+#    #+#             */
/*   Updated: 2025/06/23 15:44:48 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void check_pid(pid_t pid)
{
    if (pid <= 0 || kill(pid, 0) == -1)
        error_exit("Invalid PID");
}

void	ack_handler(int sig)
{
	(void)sig;
}

void	send_bit(pid_t pid, int bit)
{
	int sig;

	if (bit)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	
	if (kill(pid, sig) == -1)
		error_exit("Erro ao enviar sinal");
	pause();
	usleep(1000);
}

void	send_number(pid_t pid, unsigned int num, int bits)
{
	int i;

	i = bits - 1;
	while (i >= 0)
	{
		send_bit(pid, (num >> i) & 1);
		i--;
	}
}

void	send_message(pid_t pid, char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		send_number(pid, (unsigned char)msg[i], 8);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t   pid;
	char    *msg;
	int     len;

	if (argc != 3)
		error_exit("Uso: ./client <PID> <mensagem>");
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	len = ft_strlen(msg);
	signal(SIGUSR1, ack_handler);
	send_number(pid, len, 32);
	send_message(pid, msg);
	return (0);
}
