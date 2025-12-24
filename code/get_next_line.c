/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:45 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/25 00:31:33 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*refine_line(char *old_stashed_data, char **full_line,
		int old_stash_len)
{
	char	*new_stashed_data;
	int		line_length;
	char	*terminator_point;

	if (old_stashed_data)
	{
		if (!old_stashed_data[0])
		{
			free(old_stashed_data);
			*full_line = NULL;
			return (NULL);
		}
		terminator_point = ft_strchr(old_stashed_data, '\n');
		if (!terminator_point)
		{
			line_length = old_stash_len;
			*full_line = ft_strdup_len(old_stashed_data, line_length);
			free(old_stashed_data);
			new_stashed_data = NULL;
			return (new_stashed_data);
		}
		else
		{
			line_length = terminator_point - old_stashed_data;
			*full_line = ft_strdup_len(old_stashed_data, line_length + 1);
			new_stashed_data = ft_strdup_len(terminator_point + 1,
					(old_stash_len - (line_length + 1)));
			free(old_stashed_data);
			return (new_stashed_data);
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *stashed_data;
	char *line_read;
	char *temp_reader;
	int bytes_read;
	int stash_len;

	line_read = NULL;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);

	temp_reader = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_reader)
		return (NULL);

	while (!ft_strchr(stashed_data, '\n'))
	{
		bytes_read = read(fd, temp_reader, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp_reader[bytes_read] = '\0';
		stashed_data = ft_str_join_and_free(stashed_data, temp_reader);
		if (!stashed_data)
			break ;
	}
	free(temp_reader);
	if (bytes_read == -1)
	{
		if (stashed_data)
			free(stashed_data);
		stashed_data = NULL;
		return (NULL);
	}
	if (stashed_data)
	{
		stash_len = ft_strlen(stashed_data);
		stashed_data = refine_line(stashed_data, &line_read, stash_len);
	}
	return (line_read);
}