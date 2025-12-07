/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:55 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/06 18:57:15 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

# include <stdio.h>

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>



void	*ft_calloc(size_t nmemb, size_t size);


#endif