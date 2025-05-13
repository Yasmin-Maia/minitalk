/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:49:08 by yasmin            #+#    #+#             */
/*   Updated: 2025/05/13 14:43:09 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handler(int signum, siginfo_t *info, void *context)
{
    static int bit_count = 0;
    static unsigned char current_char = 0;

	(void)info;
    (void)context; // evitar warning

    if (signum == SIGUSR1)
        current_char |= (1 << (7 - bit_count)); // adiciona bit 1
    // se SIGUSR2, bit já é 0, então não precisa mexer

    bit_count++;

     if (bit_count == 8)
    {
        if (current_char == '\0') 
        {
            write(1, "\n", 1);
            kill(info->si_pid, SIGUSR1);  // Envia confirmação para o cliente
        } 
        else 
        {
            write(1, &current_char, 1);
        }
        bit_count = 0;
        current_char = 0;
    }
}

void confirmation_handler(int signum)
{
    if (signum == SIGUSR1) {
        write(1, "Mensagem entregue com sucesso!\n", 31);
        exit(0);  // Encerra o cliente após receber confirmação
    }
}

int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = &handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    pid_t pid = getpid();
    printf("Servidor rodando. PID: %d\n", pid);

    while (1)
        pause();
}

