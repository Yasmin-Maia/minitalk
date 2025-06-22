/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:32:59 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/22 21:08:01 by ymaia-do         ###   ########.fr       */
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

#define BIT_SLEEP_TIME 100
#define MSG_RECEIVED "Mensagem recebida!\n"

typedef int pid_t;

typedef struct s_server_data
{
    char    *buffer;
    int     buf_len;
    int     bit_count;
    unsigned char   current_char;
}   t_server_data;



#endif
