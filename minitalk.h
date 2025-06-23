/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:32:59 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/23 23:54:40 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>

char	*append_char_to_buffer(char *buffer, char c, int *len);
void	process_end_message(char **buffer, int *len, pid_t client_pid);
void	process_char(char c, char **buffer, int *len);
void	error_exit(char *msg);

#endif
