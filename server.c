/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:49:08 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/22 21:03:02 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int g_fullsize = 0;

void error_exit(char *msg)
{
    ft_putendl_fd(msg, 2);
    exit(1);
}

char *create_char(void)
{
    char *new_buf;

    new_buf = ft_calloc((g_fullsize + 1), sizeof(char));
    if (!new_buf)
        error_exit("Error: Memory allocation failed");
    return new_buf;
}

void    printall( char **buffer)
{
	if(*buffer)
	{
		(*buffer)[g_fullsize] = '\0';
		ft_printf("%s\n", *buffer);
		free (*buffer);
		*buffer = NULL;
	}
	g_fullsize = 0;
}

void fullsize(int sig)
{
	static int	size = 0;
	static int	countbit = 0;

	if (sig == SIGUSR1)
		size = (size << 1) | 1;
	else
		size = size << 1;
	countbit++;
	if (countbit == 32)
	{
		g_fullsize = size;
		ft_printf("size: %d\n", g_fullsize);
		countbit = 0;
		size = 0;
	}
	
}

void handler(int signum)
{
    static int countbit = 0;
    static unsigned char current_char = 0;
    static char *buffer = NULL;
    static int buf_len = 0;

    if (signum == SIGUSR1)
        current_char |= (1 << (7 - countbit));
    countbit++;

    if (countbit == 8)
    {
        if (buffer == NULL && g_fullsize > 0)
            buffer = create_char();
        if (buffer && buf_len < g_fullsize)
			buffer[buf_len++] = current_char;
        countbit = 0;
        current_char = 0;
    }
    if (buf_len == g_fullsize && g_fullsize > 0)
    {
		printall(&buffer);
        buf_len = 0;
    }
}

int main(void)
{
    pid_t pid = getpid();
	
    printf("Servidor rodando. PID: %d\n", pid);
	signal(SIGUSR1, fullsize);
	signal(SIGUSR2, fullsize);	
    while (1)
    {
		if (g_fullsize == 0)
		{
			signal(SIGUSR1, fullsize);
			signal(SIGUSR2, fullsize);
		}
		else
		{
			signal (SIGUSR1, handler);
			signal (SIGUSR2, handler);
		}
		pause();
	}
	return (0);
}
