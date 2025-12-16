/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:45 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/16 19:48:49 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



// char *check_linebreak(char *read_so_far)
// {
// 	int i;

// 	i = 0;
// 	while(r(read_so_far[i]!='\n') && (read_so_far[i]!='\0'))
// 		i++;
	
// }






int has_line_termination(char *text_loaded, int len)
{
	int i;

	i=0;
	while(i < len)
	{
		if((text_loaded[i] == '\n') || (text_loaded[i] == '\0'))
			return(i);
		i++;
	}
	return (-1);
}


char *get_next_line(int fd)
{
	//stash for the entire data read
	static char *stashed_data;

	char *line_read;

	char *temp_reader;
	int bytes_read;
	int line_terminator;

	if(fd == -1)
		return (NULL);

	temp_reader = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!temp_reader)
		return (NULL);


	line_terminator = -1;
	while(line_terminator == -1)
	{
		bytes_read = read(fd, temp_reader, BUFFER_SIZE);
		temp_reader[bytes_read] = '\0';
		if(bytes_read >= 0)
		{
			line_terminator = has_line_termination(temp_reader, bytes_read);
			stashed_data = ft_strjoin(stashed_data, temp_reader);
		}
		else
			break;
		
	}
	free(temp_reader);
	return(stashed_data);
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