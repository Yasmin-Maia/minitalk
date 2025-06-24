/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:43:06 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 23:46:41 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	append_char_to_buffer(t_msg **list, char c)
{
	t_msg	*new_c;
	t_msg	*tmp;

	new_c = malloc(sizeof(t_msg));
	if (new_c == NULL)
		exit(1);
	new_c->c = c;
	new_c->next = NULL;
	if (*list == NULL)
		*list = new_c;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_c;
	}
}

static void	free_list(t_msg **list)
{
	t_msg	*tmp;
	t_msg	*next;

	if (*list == NULL || ((*list)->c == '\0' && (*list)->next == NULL))
		ft_printf("\n");
	else
	{
		tmp = *list;
		while (tmp != NULL)
		{
			ft_printf("%c", tmp->c);
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		ft_printf("\n");
	}
	*list = NULL;
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static t_msg	*str_list = NULL;
	static int		bit_count = 0;
	static char		current_char = 0;

	(void)context;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		current_char = (current_char << 1) | (sig == SIGUSR2);
		bit_count++;
		if (bit_count == 8)
		{
			append_char_to_buffer(&str_list, current_char);
			if (current_char == '\0')
			{
				free_list(&str_list);
				kill(info->si_pid, SIGUSR2);
			}
			bit_count = 0;
			current_char = 0;
		}
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	sa.sa_sigaction = &handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	ft_printf("Server PID: %d\n", (int)pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
