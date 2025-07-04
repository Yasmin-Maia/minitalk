/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:30 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/22 19:51:28 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_size(pid_t pid, int size)
{
    int bit;
    
    bit = 31;
    while (bit >= 0) {
        if (size & (1 << bit))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(BIT_SLEEP_TIME);
        bit--;
    }
}

void send_str(pid_t pid, char *str, int size)
{
    int bit;
	int i;

    bit = 0;
	i = 0;
    while(bit < size)
    {
		i = 8;
		while (i > 0)
		{
			if (str[bit] & 0b10000000)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			str[bit] = str[bit] << 1;
			i--;
			usleep(BIT_SLEEP_TIME);
		}
        bit++;
    }
}

void ack_handler(int sig)
{
    if (sig == SIGUSR1)
    {
        write(1, "Mensagem recebida!\n", 20);
        exit(0);
    }
}

void    error_exit(char *msg)
{
    ft_putendl_fd(msg, 2);
    exit(1);
}

int main(int argc, char **argv)
{
	pid_t   pid;
	char    *msg;
	int     len;
	
	if (argc != 3)
	error_exit("Use: ./client <PID> <mensagem>\n");
	msg = argv[2];
	len = ft_strlen(msg);
	pid = ft_atoi(argv[1]);
	ft_printf("%d\n", len);
	send_size(pid, len);
	send_str(pid, msg, len);
	return (0);
}