/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 00:04:04 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 00:04:33 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*append_char_to_buffer(char *buffer, char c, int *len)
{
	char	*new_buffer;
	int		i;

	new_buffer = ft_calloc(*len + 2, sizeof(char));
	if (!new_buffer)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	i = 0;
	if (buffer)
	{
		while (i < *len)
		{
			new_buffer[i] = buffer[i];
			i++;
		}
		free(buffer);
	}
	new_buffer[i] = c;
	new_buffer[i + 1] = '\0';
	(*len)++;
	return (new_buffer);
}

void	process_end_message(char **buffer, int *len, pid_t client_pid)
{
	if (*buffer)
	{
		ft_printf("%s\n", *buffer);
		free(*buffer);
		*buffer = NULL;
		*len = 0;
	}
	usleep(1000);
	kill(client_pid, SIGUSR1);
}

void	process_char(char c, char **buffer, int *len)
{
	*buffer = append_char_to_buffer(*buffer, c, len);
	if (!*buffer)
	{
		ft_putendl_fd("Erro de alocação", 2);
		exit(1);
	}
}

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}
