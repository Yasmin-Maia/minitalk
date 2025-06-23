/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:43:06 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 00:02:17 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	static int		bit_count = 0;
	static char		current_char = 0;
	static char		*message_buffer = NULL;
	static int		buffer_len = 0;

	(void)context;
	if (sig == SIGUSR1)
		current_char = (current_char << 1) | 1;
	else if (sig == SIGUSR2)
		current_char = (current_char << 1);
	else
		return ;
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
			process_end_message(&message_buffer, &buffer_len, info->si_pid);
		else
			process_char(current_char, &message_buffer, &buffer_len);
		bit_count = 0;
		current_char = 0;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", (int)pid);
	setup_signals();
	while (1)
		pause();
	return (0);
}
