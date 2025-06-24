/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:32:59 by yasmin            #+#    #+#             */
/*   Updated: 2025/06/24 17:22:19 by ymaia-do         ###   ########.fr       */
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

typedef struct s_msg
{
	char	*buffer;
	size_t 	len;
	size_t	all_len;
} t_msg;

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	error_exit(char *msg);

#endif
