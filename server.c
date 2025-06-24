/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:43:06 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 18:26:19 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


static t_msg	g_msg = {NULL, 0, 0};

void	append_char_to_buffer(char c)
{
	if (!g_msg.buffer)
	{
		g_msg.buffer = ft_calloc(1024, sizeof(char));
		g_msg.all_len = 1024;
	}
	if (g_msg.len + 1 >= g_msg.all_len)
	{
		g_msg.all_len += 1024;
		g_msg.buffer = ft_realloc(g_msg.buffer, g_msg.len, g_msg.all_len);
		if (!g_msg.buffer)
			ft_printf("Error: Memory allocation failed\n");
	}
	g_msg.buffer[g_msg.len++] = c;
	g_msg.buffer[g_msg.len] = '\0';
}

void	process_end_message(void)
{

	if (g_msg.buffer)
	{
		ft_printf("%s\n", g_msg.buffer);
		free(g_msg.buffer);
		g_msg.buffer = NULL;
		g_msg.len = 0;
		g_msg.all_len = 0;
	}
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int		bit_count;
	static char		current_char;

	(void)context;
	if (sig == SIGUSR1)
		current_char = (current_char << 1) | 1;
	else if (sig == SIGUSR2)
		current_char = (current_char << 1);
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf("%d\n", g_msg.len);
		if (current_char == '\0')
		{
			ft_printf("%s\n", g_msg.buffer);
			free(g_msg.buffer);
			g_msg = (t_msg){NULL, 0, 0};
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			append_char_to_buffer(current_char);
			kill(info->si_pid, SIGUSR1);
		}
		bit_count = 0;
		current_char = 0;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	g_msg.buffer = ft_calloc(1, 1024);
	g_msg.all_len = 1024;
	ft_printf("Server PID: %d\n", (int)pid);
	setup_signals();
	while (1)
		pause();
	return (0);
}
