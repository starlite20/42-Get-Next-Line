/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:51 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/25 00:28:13 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			actual_size;
	unsigned char	*c_ptr;
	size_t			i;

	if ((size > 0 && (nmemb > (SIZE_MAX / size))))
		return (NULL);
	actual_size = nmemb * size;
	ptr = malloc(actual_size);
	if (!ptr)
		return (NULL);
	i = 0;
	c_ptr = (unsigned char *)ptr;
	while (i < actual_size)
		*(c_ptr + i++) = 0;
	return (ptr);
}

char	*ft_strdup_len(const char *s, int copy_len)
{
	char	*ptr;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (copy_len < len)
		len = copy_len;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(ptr + i) = *(s + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

char	*ft_str_join_and_free(char *s1, char *s2)
{
	char			*concatenated;
	unsigned int	s1_len;
	unsigned int	i;
	unsigned int	si;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	concatenated = malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (!concatenated)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	si = 0;
	while (si < (s1_len))
		*(concatenated + i++) = *(s1 + si++);
	si = 0;
	while (si < (ft_strlen(s2)))
		*(concatenated + i++) = *(s2 + si++);
	*(concatenated + i) = '\0';
	free(s1);
	return (concatenated);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	character;

	character = (unsigned char)c;
	if (!s)
		return (NULL);
	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == character)
			return ((char *)(s + i));
		i++;
	}
	if (*(s + i) == character)
		return ((char *)(s + i));
	return (NULL);
}
