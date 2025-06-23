/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:32:59 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/23 15:53:19 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>

typedef int pid_t;

typedef struct s_server_data
{
    char    *buffer;
    int     buf_len;
    int     bit_count;
    unsigned char   current_char;
    int     receiving_size;
    int     size_bits;
    int     total_size;
}   t_server_data;

void init_server_data(void);
void handle_signal(int sig, siginfo_t *info, void *context);
void error_exit(char *msg);
void ack(pid_t client_pid);
void receive_size(int sig, siginfo_t *info);
void receive_msg(int sig, siginfo_t *info);

#endif
