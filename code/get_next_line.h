/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:55 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/16 20:42:45 by ssujaude         ###   ########.fr       */
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

//check
# include <stdint.h>



void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_str_join_and_free(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup_len(const char *s, int copy_len);
char	*ft_strchr(const char *s, int c);


#endif