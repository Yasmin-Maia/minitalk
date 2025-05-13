/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:30 by yasmin            #+#    #+#             */
/*   Updated: 2025/05/13 14:39:16 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_char(pid_t pid, char c)
{
    int bit;

    bit = 0;
    while(bit < 8)
    {
        if ((c >> (7 - bit)) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(500);
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
    
    if (argc != 3)
        error_exit("Usage: ./client <PID> <mensagem>\n");
    pid = ft_atoi(argv[1]);
    msg = argv[2];
    signal(SIGUSR1, ack_handler);
    while (*msg)
        send_char(pid, *msg++);

    // Envia '\0' no final como sinal de fim (opcional)
    send_char(pid, '\0');
    pause();
    return 0;
}