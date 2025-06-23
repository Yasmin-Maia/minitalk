/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:51:15 by ymaia-do          #+#    #+#             */
/*   Updated: 2025/06/23 15:49:22 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_server_data g_data;

void init_server_data(void)
{
	if (g_data.buffer)
	{
		free(g_data.buffer);
		g_data.buffer = NULL;
	}
	ft_bzero(&g_data, sizeof(t_server_data));
	g_data.receiving_size = 1;
}

void handle_signal(int sig, siginfo_t *info, void *context)
{
    (void)context;
    
    if (g_data.receiving_size)
        receive_size(sig, info);
    else
        receive_msg(sig, info);
    
    ack(info->si_pid);
}

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	ack(pid_t client_pid)
{
	kill(client_pid, SIGUSR1);
}

void    receive_size(int sig, siginfo_t *info)
{
    (void)info;
    
    if (sig == SIGUSR1)
        g_data.total_size = (g_data.total_size << 1) | 1;
    else
        g_data.total_size = g_data.total_size << 1;
    
    g_data.size_bits++;
    
    if (g_data.size_bits == 32)
    {
        if (g_data.total_size == 0 || g_data.total_size > 1000000)
        {
            init_server_data();
            return;
        }
        g_data.buffer = ft_calloc(g_data.total_size + 1, sizeof(char));
        if (!g_data.buffer)
        {
            init_server_data();
            return;
        }
        g_data.receiving_size = 0;
        g_data.size_bits = 0;
    }
}

void    receive_msg(int sig, siginfo_t *info)
{
    (void)info;
    
    if (sig == SIGUSR1)
        g_data.current_char |= (1 << (7 - g_data.bit_count));
    
    g_data.bit_count++;
    
    if (g_data.bit_count == 8)
    {
        if (g_data.buf_len < g_data.total_size)
            g_data.buffer[g_data.buf_len++] = g_data.current_char;
        g_data.bit_count = 0;
        g_data.current_char = 0;
    }
    
    if (g_data.buf_len == g_data.total_size && g_data.total_size > 0)
    {
        ft_printf("%s\n", g_data.buffer);
        init_server_data();
    }
}

int main(void)
{
    struct sigaction sa;
    
    ft_printf("Server PID: %d\n", getpid());
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        error_exit("Error setting up SIGUSR1");
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
        error_exit("Error setting up SIGUSR2");
    
    init_server_data();
    while (1)
        pause();
    return (0);
}