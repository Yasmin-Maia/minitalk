/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:49:08 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/19 21:20:56 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define BIT_SLEEP_TIME 500  // Microssegundos entre envios de bits
#define MSG_RECEIVED "Mensagem recebida!\n"

void error_exit(char *msg)
{
    ft_putendl_fd(msg, 2);
    exit(1);
}

char *append_char(char *buffer, size_t *len, char c)
{
    char *new_buf;
    size_t i;

    new_buf = ft_calloc(*len + 2, sizeof(char)); // +1 para novo char, +1 para '\0'
    if (!new_buf)
        return NULL;
    i = 0;
    while (i < *len)
    {
        new_buf[i] = buffer[i];
        i++;
    }
    new_buf[i] = c;
    if (buffer)
        free(buffer);
    *len += 1;
    return new_buf;
}

void handler(int signum, siginfo_t *info, void *context)
{
    (void)context;
    static int bit_count = 0;
    static unsigned char current_char = 0;
    static char *buffer = NULL;
    static size_t buf_len = 0;

    if (signum == SIGUSR1)
        current_char |= (1 << (7 - bit_count));
    bit_count++;

    if (bit_count == 8)
    {
        if (current_char == '\0')
        {
            if (buffer)
            {
                write(1, buffer, buf_len);
                write(1, "\n", 1);
                free(buffer);
                buffer = NULL;
                buf_len = 0;
            }
            kill(info->si_pid, SIGUSR1);
        }
        else
        {
            buffer = append_char(buffer, &buf_len, current_char);
            if (!buffer)
                error_exit("Erro de alocação");
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

void handle_interrupt(int sig) {
    (void)sig;
    write(1, "\nPrograma encerrado.\n", 21);
    exit(0);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = &handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    signal(SIGINT, handle_interrupt);

    pid_t pid = getpid();
    printf("Servidor rodando. PID: %d\n", pid);

    while (1)
        pause();
    
    return 0;
}
