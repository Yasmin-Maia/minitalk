/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:51:05 by ymaia-do          #+#    #+#             */
/*   Updated: 2025/06/23 19:24:32 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_char(pid_t pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        if ((c >> bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        bit--;
        usleep(200); // tempo um pouco maior para segurança com Valgrind
    }
}

void send_str(pid_t pid, char *str)
{
    int i = 0;
    while (str[i])
    {
        send_char(pid, str[i]);
        i++;
    }
    send_char(pid, '\0'); // envia byte nulo no final
}

void    error_exit(char *msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}

int main(int argc, char **argv)
{
    pid_t pid;

    if (argc != 3)
        error_exit("Use: ./client <PID> <mensagem>\n");

    pid = atoi(argv[1]);
    send_str(pid, argv[2]);

    return (0);
}
