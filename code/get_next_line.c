/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:45 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/17 00:31:17 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"




char *refine_line(char *old_stashed_data, char **full_line, int old_stash_len)
{
	char *new_stashed_data;
	int i;
	int line_length;
	char *terminator_point;

	if(old_stashed_data)
	{
		terminator_point = ft_strchr(old_stashed_data, '\n');
		// if no \n... indicating \0 EOF existance
		if(!terminator_point)
		{
			line_length = old_stash_len;
			*full_line = ft_strdup_len(old_stashed_data, line_length + 1);
			//new_stashed_data = ft_strdup_len(old_stashed_data, (old_stash_len - line_length + 1));
			free(old_stashed_data);
			new_stashed_data = NULL;
			return (new_stashed_data);
		}
		else
		{
			line_length = terminator_point - old_stashed_data;
			*full_line = ft_strdup_len(old_stashed_data, line_length + 1);
			new_stashed_data = ft_strdup_len(terminator_point + 1, (old_stash_len - (line_length + 1)));
			free(old_stashed_data);
			return (new_stashed_data);
		}
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
	int stash_len;

	if(fd == -1)
		return (NULL);

	temp_reader = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!temp_reader)
		return (NULL);

	printf("\n\n## gnl stashed is [%s] ##\n", stashed_data);

	while(!ft_strchr(stashed_data, '\n'))
	{
		printf("\n \t ==> gnl looping : [%s]", stashed_data);
		bytes_read = read(fd, temp_reader, BUFFER_SIZE);
		if(bytes_read <= 0)
			break;

		temp_reader[bytes_read] = '\0';
		stashed_data = ft_str_join_and_free(stashed_data, temp_reader);
	}
	if(ft_strchr(stashed_data, '\n'))
	{
		stash_len = ft_strlen(stashed_data);

		printf("\n gnl  BEFR REFINE ==> %s ", stashed_data);
		stashed_data = refine_line(stashed_data, &line_read, stash_len);
		printf("\n gnl  AFTR REFINE ==> %s ", stashed_data);
	}
	else
	{
		stash_len = ft_strlen(stashed_data);

		printf("\n gnl  BEFR REFINE ==> %s ", stashed_data);
		stashed_data = refine_line(stashed_data, &line_read, stash_len);
		printf("\n gnl  AFTR REFINE ==> %s ", stashed_data);
	}
	
	free(temp_reader);
	return(line_read);
}






int main()
{
	int fd;
	char *line_read = "";

	fd = open("text.txt", O_RDONLY);
	printf("\n== > file descriptor id : %d\n*****************\n\n", fd);

	if(fd == -1)
		return (0);
	while(line_read = get_next_line(fd))
	{
		if(line_read)
			printf("\n ##MAIN## \t\t LINE FOUND - [%s] -\n", line_read);
		free(line_read);
	}

	close(fd);

	printf("\n \n== > file closed");
	return(0);
}