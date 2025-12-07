/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:51 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/06 18:27:57 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	actual_size;
	unsigned char	*c_ptr;
	int i;

	if ((size > 0 && (nmemb > (SIZE_MAX / size))))
		return (NULL);
	actual_size = nmemb * size;
	ptr = malloc(actual_size);
	if (!ptr)
		return (NULL);
	i = 0;
	c_ptr = (unsigned char*)ptr;
	while(i < actual_size)
		*(c_ptr + i++) = 0;
	return (ptr);
}
