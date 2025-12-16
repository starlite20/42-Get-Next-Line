/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:45 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/16 21:22:24 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"




char *refine_line(char *old_stashed_data, char **full_line)
{
	char *new_stashed_data;
	int i;
	int line_length;

	line_length = ft_strchr(old_stashed_data, '\n') - old_stashed_data;
	if(line_length > 0)
	{
		*full_line = ft_strdup_len(old_stashed_data, line_length + 1);
		new_stashed_data = ft_strdup_len(ft_strchr(old_stashed_data, '\n') + 1, ft_strlen(old_stashed_data));
		free(old_stashed_data);
		return (new_stashed_data);
	}
	return(NULL);
}


char *get_next_line(int fd)
{
	//stash for the entire data read
	static char *stashed_data;

	char *line_read;

	char *temp_reader;
	int bytes_read;

	if(fd == -1)
		return (NULL);

	temp_reader = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!temp_reader)
		return (NULL);

	printf("\n\n## gnl stashed is [%s] ##\n", stashed_data);

	while(!ft_strchr(stashed_data, '\n'))
	{
		bytes_read = read(fd, temp_reader, BUFFER_SIZE);
		if(bytes_read <= 0)
			break;

		temp_reader[bytes_read] = '\0';
		stashed_data = ft_str_join_and_free(stashed_data, temp_reader);
	}
	if(stashed_data)
	{
		printf("\n gnl  BEFR REFINE ==> %s ", stashed_data);
		stashed_data = refine_line(stashed_data, &line_read);
		printf("\n gnl  AFTR REFINE ==> %s ", stashed_data);
	}
	
	free(temp_reader);
	return(line_read);
}

int main()
{
	int fd;
	char *line_read;

	fd = open("text.txt", O_RDONLY);
	printf("\n== > file descriptor id : %d\n*****************\n\n", fd);

	if(fd == -1)
		return (0);
	line_read = get_next_line(fd);
	while(line_read)
	{
		printf("\n- [%s] -\n", line_read);
		line_read = get_next_line(fd);
	}

	free(line_read);
	close(fd);

	printf("\n \n== > file closed");
	return(0);
}