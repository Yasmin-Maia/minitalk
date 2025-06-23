/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:49:08 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/23 18:28:49 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

/* static void	handle_char(char ch, char **str)
{
	char	temp[2];
	char	*new_str;

	temp[0] = ch;
	temp[1] = '\0';
	if (!*str)
		*str = ft_strdup(temp);
	else if (ch == 0)
	{
		ft_printf("%s\n", *str);
		free(*str);
		*str = NULL;
	}
	else
	{
		new_str = ft_strjoin(*str, temp);
		free(*str);
		*str = ft_strdup(new_str);
		free(new_str);
	}
} */

void handle_signal(int sig, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    static int bit = 0;
    static char ch = 0;
    static char *str = NULL;
    char temp[2];
    char *new_str;

    if (sig == SIGUSR1)
        ch |= (1 << (7 - bit));
    if (sig == SIGUSR2)
        ch &= ~(1 << (7 - bit));
    bit++;
    if (bit == 8)
    {
        temp[0] = ch;
        temp[1] = '\0';
        if (!str)
            str = ft_strdup(temp);
        else if (ch == '\0')
        {
            ft_printf("%s\n", str);
            free(str);
            str = NULL;
        }
        else
        {
            new_str = ft_strjoin(str, temp);
            free(str);
            str = ft_strdup(new_str);
            free(new_str);
        }
        bit = 0;
        ch = 0;
    }
}

int main(void)
{
    struct sigaction sig;

    ft_printf("Server PID: %d\\n", getpid());

    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = handle_signal;
    sigemptyset(&sig.sa_mask);
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);

    while (1)
        pause();
}