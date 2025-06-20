/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:32:59 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/19 21:18:00 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>

typedef int pid_t;

// Se quiser, declare uma struct aqui (por enquanto não é obrigatório)
typedef struct s_message
{
    int             bit_count;
    unsigned char   current_char;
}   t_message;

// Declarações de funções
void    send_char(pid_t pid, char c); // do cliente
char *append_char(char *buffer, size_t *len, char c);

#endif
